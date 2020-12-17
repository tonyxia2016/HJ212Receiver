# HJ212Receiver
本仓库是根据《污染物在线监控（监测）系统数据传输标准 HJ 212-2017.pdf》文档，对接收到的212协议报文进行接收和解析。采用C++ boost asio网络库编写TCP服务端进行212数据的接收，我开发本项目时采用[boost](https://www.boost.org/)版本使用的是1.69.0，目前官方最新boost库版本是1.75.0；并使用[yaml-cpp](https://github.com/jbeder/yaml-cpp)作为yaml配置文件的解析库。已经在Windows10和VS2017环境下进行编译测试；并且在CentOS8下使用cmake进行编译测试过。
