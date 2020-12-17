#pragma once
#include <type.h>


namespace network
{
	struct ProtoRequest {
		String		address;	// 远程地址
		uint16		port;	  // 远程端口
		String		body;	  // 数据内容
		StringArray Ids;		  // 远程标识
		String		ST;
	};

	struct ProtoResponse {
		StringArray Ids;			// 远程标识
		StringArray bodys;	// 响应数据
		String		ST;
	};

	class DataSink
	{
	public:
		// "请求-回复"模式
		virtual void ReqRep(const ProtoRequest& req, ProtoResponse& res) = 0;

	};

	class MgrInterface {
	public:
		// 数据发送
		virtual bool write_data(const String& clientid, const String& req) = 0;
	};
}

