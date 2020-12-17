#pragma once
#include <type.h>
#include <my_log.h>
#include <boost/asio.hpp>
#include <DataQueue.h>

using boost::asio::ip::tcp;

namespace network 
{
	class DataSink;
	class ConnectionManager;
	class Connection : public boost::noncopyable, public std::enable_shared_from_this<Connection>
	{
	public:
		Connection(tcp::socket socket, ConnectionManager& manager, DataSink& sink);

		tcp::socket& socket() {
			return socket_;
		}

		StringArray client_ids() const {
			return clientids_;
		}

		bool find_id(const String& clientid) const {
			auto fi = std::find_if(clientids_.begin(), clientids_.end(), [&clientid](const String& i) {
				return i == clientid;
			});
			return fi != clientids_.end();
		}

		void set_client_id(const String& clientid) {
			if (clientid.size()) {
				if (!find_id(clientid)) {
					clientids_.emplace_back(clientid);
				}
			}
		}

		void set_client_id(const StringArray& clientids) {
			for (auto& i : clientids) {
				set_client_id(i);
			}
		}

		void start(bool bPassiveMode, const String& msg = "") {
			if (bPassiveMode) {
				if (msg.size()) {
					write_data(msg);
				}
			}
			else {
				do_read();
			}
		}

		void stop() {
			socket_.close();
		}

		bool write_data(const String& buffer)
		{
			Uint8Array req;
			std::copy(buffer.begin(), buffer.end(), std::back_inserter(req));
			do_write(req);
			return true;
		}

		bool write_data(const Uint8Array& buffer)
		{
			do_write(buffer);
			return true;
		}

	protected:
		void do_read() 
		{
			auto self(shared_from_this());
			socket_.async_read_some(boost::asio::buffer(read_buffer_, max_buffer_size), [this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
				if (!ec) {
					Uint8sArray arr;
					handle_read(bytes_transferred, arr);
					for (auto& i : arr) {
						do_write(i);
					}
					do_read();
				}
				else {
// 					if (ec.value() == boost::asio::error::connection_reset || ec.value() == boost::asio::error::connection_aborted) {
// 					}
					do_close();
				}
			});
		}

		void do_write(const Uint8Array& buffer)
		{
			bool is_empty = write_queue_.empty();
			write_queue_.push_back(buffer);
			if (is_empty) {
				do_write();
			}
		}

		void do_write()
		{
			auto self(shared_from_this());
			boost::asio::async_write(socket_, boost::asio::buffer(write_queue_.front()), [this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
				if (!ec) {
					write_queue_.pop_front();
					if (write_queue_.size()) {
						msleep(100);
						do_write();
					}
				}
				else {
					if (ec.value() == boost::asio::error::connection_reset || ec.value() == boost::asio::error::connection_aborted) {

					}
					do_close();
				}
			});
		}

		void do_close();

	protected:
		virtual void handle_read(std::size_t bytes_transferred, Uint8sArray& res);


	private:
		tcp::socket socket_;
		// 接收数据缓存
		enum {
			max_buffer_size = 8192,
		};
		// 数据接收缓存
		char read_buffer_[max_buffer_size];

		// 数据发送队列
		RMQ::DataQueue write_queue_;

		StringArray clientids_;

		String st_;

		ConnectionManager& manager_;

		DataSink& data_sink_;
	};
	typedef std::shared_ptr<Connection> ConnectionPtr;
}


