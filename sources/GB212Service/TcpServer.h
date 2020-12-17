#pragma once
#include <type.h>
#include <my_log.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "Connection.h"
#include "ConnectionManager.h"
#include "net.h"
#include <algorithm>

namespace network
{
	class TcpServer : public my_log
	{
	public:
		TcpServer(sig_log& lg, ConnectionManager& manager, DataSink& sink) : my_log(lg)
			, io_context_(1)
			, acceptor_(io_context_)
			, socket_(io_context_)
			, manager_(manager)
			, data_sink_(sink) 
		{
		}

		// 启动服务器
		bool start(const String& addr, const int32& port) {
			try
			{
				io_context_.reset();
				boost::asio::ip::tcp::resolver resolver(io_context_);
//				boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(addr, port).begin();
				boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(addr), port);
				acceptor_.open(endpoint.protocol());
				acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
				acceptor_.bind(endpoint);
				acceptor_.listen();
				do_accept();
				size_t thread_count = std::max(boost::thread::hardware_concurrency() * 2 + 1, uint32(10));
				for (size_t i = 0; i < thread_count; i++) {
					threads_.create_thread(boost::bind(&boost::asio::io_context::run, &io_context_));
				}
				EmitLog(info, "Startup TCP Server on[%s:%d] Successful.", addr.c_str(), port);
			}
			catch (const boost::system::system_error& e)
			{
				EmitLog(error, "Startup TCP Server Failed: %s", e.what());
				return false;
			}
			return true;
		}

		// 停止服务器
		void stop() {
			acceptor_.close();
			manager_.stop_all();
			io_context_.stop();
			threads_.join_all();
		}

	protected:
		// 监听
		void do_accept() {
 			acceptor_.async_accept(socket_, boost::bind(&TcpServer::handle_accept, this, boost::asio::placeholders::error));
		}

		// 监听句柄
		void handle_accept(const boost::system::error_code& ec) {
			if (!acceptor_.is_open()) {
				return;
			}
			if (!ec) {
				manager_.start(std::make_shared<Connection>(std::move(socket_), manager_, data_sink_));
			}
			do_accept();
		}


	private:
		boost::asio::io_context			io_context_;
		boost::asio::ip::tcp::acceptor	acceptor_;
		boost::asio::ip::tcp::socket	socket_;
		boost::thread_group				threads_;

		// TCP连接管理对象
		ConnectionManager&				manager_;
		// 数据接口（请求-回复模式）
		DataSink&						data_sink_;
	};
}

