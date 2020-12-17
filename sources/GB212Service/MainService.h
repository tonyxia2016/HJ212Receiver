#pragma once
#include <my_log.h>
#include "TcpServer.h"
#include "GB212DataMiddleware.h"
#include "ConfigY.h"
#include "ConfigYWriter.h"


class MainService : public my_log
{
public:
	MainService(sig_log& lg, int argc, char* argv[]);

	void start();

	void stop();

private:

	ConfigY	cfg_;
	String  cfgpath_;
	ConfigOpt cfg_opt_;

	// 212协议 TCP服务类对象
	network::TcpServer	gb212_tcp_server_;
	network::ConnectionManager	gb212_conn_mgr_;
	GB212DataMiddleware		gb212_data_process_;
};