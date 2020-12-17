#pragma once
#include <type.h>
#include <my_log.h>
#include <func.h>
#include "MainService.h"
#include <mutex>

class MainApp : public my_log
{
public:
	MainApp(int argc, char* argv[]);
	~MainApp();

	// 运行服务, basync表示是否异步还是同步阻塞
	void run(bool basync = false);

	// 停止服务
	void stop();

protected:
	// 初始化函数
	void init();

	// 主服务入口函数
	void start();

	// 日志信息回调函数
	void slot_log(const char * file, const char * func, long line, log_level level, bool need_send, const char * msg);

	// set current work dir
	bool set_work_dir(const char* exe_path);

private:
	sig_log			sig_log_;
	// 主线程
	Thread			thread_main_;
	// 主线程结束标志
	volatile bool	brun_main_ = false;

	MainService		main_serv_;

	std::mutex		mtx_log_;
};

