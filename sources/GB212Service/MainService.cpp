#include "MainService.h"
#include <func.h>

#include "GB212.h"


MainService::MainService(sig_log& lg, int argc, char* argv[])
	: my_log(lg)
	, gb212_conn_mgr_(lg)
	, gb212_tcp_server_(lg, gb212_conn_mgr_, gb212_data_process_)
	, cfg_(lg)
{
	if (argc > 1) {
		cfgpath_ = argv[1];
	}
}


void MainService::start()
{
	// get config 
	if (!cfg_.GetConfig(cfg_opt_, cfgpath_.c_str())) {
		return;
	}
	auto& info = cfg_opt_;


	// start data tcp server
	if (info.tcp.enable) {
		gb212_tcp_server_.start(info.tcp.host, info.tcp.port);
		EmitLog(info, "GB212Receiver Tcp Server start at port: %d", info.tcp.port);
	}
}

void MainService::stop()
{
	gb212_tcp_server_.stop();
}
