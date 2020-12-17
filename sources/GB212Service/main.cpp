// MainService.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include "MainApp.h"


int main(int argc, char* argv[])
{
#ifdef WIN32
	// 去掉菜单栏关闭按钮
	/*DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
	DrawMenuBar(GetConsoleWindow());*/
#endif

	MainApp app(argc, argv);
	app.run(true);

#ifdef _WIN32
	getchar();
	getchar();
#else
	for (; ;) {
		msleep(1000);
	}
#endif
}
