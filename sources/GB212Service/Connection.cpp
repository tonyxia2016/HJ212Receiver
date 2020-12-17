#include "Connection.h"
#include "ConnectionManager.h"
#include "net.h"

namespace network
{

	Connection::Connection(tcp::socket socket, ConnectionManager& manager, DataSink& sink)
		: socket_(std::move(socket))
		, manager_(manager)
		, data_sink_(sink)
	{
	}

	void Connection::do_close() {
		manager_.stop(shared_from_this());
	}

	void Connection::handle_read(std::size_t bytes_transferred, Uint8sArray& res) {
		auto endpoint = socket_.remote_endpoint();
		String str(read_buffer_, bytes_transferred);
#if defined(_WIN32) && defined(_DEBUG)
		printf("[%s:%d]=> %s\r\n", endpoint.address().to_string().c_str(), endpoint.port(), str.c_str());
#endif

		// [in] 接收的数据
		// [out] 客户端标识ID
		// [out] 响应的命令列表
		ProtoResponse protores;
		data_sink_.ReqRep(ProtoRequest{ endpoint.address().to_string() ,endpoint.port(), str, client_ids(), st_ }, protores);
		this->set_client_id(protores.Ids);
		this->st_ = protores.ST;
		for (auto& i : protores.bodys) {
			res.emplace_back(Uint8Array(i.begin(), i.end()));
		}
		
	}
}
