#pragma once
#include "type.h"

#define OPEQ(name) this->name = rhs.name;

// TopicOpt 订阅的主题
struct TopicOpt {
	TopicOpt& operator=(const TopicOpt& rhs) {
		if (this != &rhs) {
			OPEQ(topic);
			OPEQ(qos);
		}
		return *this;
	}

	String	topic;
	int32	qos;
};
typedef std::vector<TopicOpt> TopicOptArray;
typedef std::map<String, TopicOptArray> TopicMap;

// MQTTConnOpt mqtt连接属性
struct MQTTConnOpt {
	MQTTConnOpt& operator=(const MQTTConnOpt& rhs) {
		if (this != &rhs) {
			OPEQ(id);
			OPEQ(type);
			OPEQ(host);
			OPEQ(port);
			OPEQ(user);
			OPEQ(password);
			OPEQ(clientid);
			OPEQ(clean);
			OPEQ(enable);
			OPEQ(subtops);
		}
		return *this;
	}
	int32 id;
	String type;
	String host;
	int32 port;
	String user;
	String password;
	String clientid;
	bool clean;
	bool enable;
	TopicMap subtops;
};
typedef std::vector<MQTTConnOpt> MQTTConnOptArray;

// SQLConnOpt sql连接属性
struct SQLConnOpt {
	SQLConnOpt& operator=(const SQLConnOpt& rhs) {
		if (this != &rhs) {
			OPEQ(enable);
			OPEQ(type);
			OPEQ(host);
			OPEQ(port);
			OPEQ(user);
			OPEQ(password);
			OPEQ(database);
			OPEQ(stationsql);
		}
		return *this;
	}
	bool enable;
	String type;
	String host;
	int32  port;
	String user;
	String password;
	String database;
	String stationsql;
};

// RedisConnOpt sql连接属性
struct RedisConnOpt {
	RedisConnOpt& operator=(const RedisConnOpt& rhs) {
		if (this != &rhs) {
			OPEQ(enable);
			OPEQ(host);
			OPEQ(port);
			OPEQ(password);
			OPEQ(index);
			OPEQ(ttl);
		}
		return *this;
	}
	bool enable;
	String host;
	int32  port;
	String password;
	int32  index;
	int32  ttl;
};

// TaskTime 任务时间
struct TaskTimeOpt {
	TaskTimeOpt& operator=(const TaskTimeOpt& rhs) {
		if (this != &rhs) {
			OPEQ(day);
			OPEQ(hour);
			OPEQ(fminute);
			OPEQ(minute);
			OPEQ(real);
			OPEQ(state);
			OPEQ(env);
			OPEQ(qc);
			OPEQ(alarm);
		}
		return *this;
	}

	int32 day = 0;
	int32 hour = 0;
	int32 fminute = 0;
	int32 minute = 0;
	int32 real = 0;
	int32 state = 0;
	int32 env = 0;
	int32 qc = 0;
	int32 alarm = 0;
};

struct ServerOpt {
	ServerOpt& operator=(const ServerOpt& rhs) {
		if (this != &rhs) {
			OPEQ(enable);
			OPEQ(host);
			OPEQ(port);
		}
		return *this;
	}
	bool enable;
	String host;
	int32 port;
};

// 组分设备（OCEC、重金属、离子色谱）的MN值
struct MNOpt {
	MNOpt& operator=(const MNOpt& rhs) {
		if (this != &rhs) {
			OPEQ(metal);
			OPEQ(ocec);
			OPEQ(ion);
		}
		return *this;
	}
	String metal;
	String ocec;
	String ion;
};

struct DeviceOpt {
	DeviceOpt& operator=(const DeviceOpt& rhs) {
		if (this != &rhs) {
			OPEQ(mn);
			OPEQ(cn);
		}
		return *this;
	}
	String mn;
	String cn;
};

// Config 配置项
struct ConfigOpt {
	ConfigOpt& operator=(const ConfigOpt& rhs) {
		if (this != &rhs) {
			OPEQ(mqtt);
			OPEQ(sqldb);
			OPEQ(redis);
			OPEQ(times);
			OPEQ(tcp);
			OPEQ(mbstcp);
			OPEQ(rpc);
			OPEQ(ws);
			OPEQ(mns);
			OPEQ(ocec);
			OPEQ(metal);
			OPEQ(ion);
			OPEQ(protocol);
			OPEQ(format);
			OPEQ(type);
			OPEQ(log);
		}
		return *this;
	}

	MQTTConnOptArray mqtt;
	SQLConnOpt sqldb;
	RedisConnOpt redis;
	TaskTimeOpt times;
	// tcp gb212
	ServerOpt tcp;
	// mbstcp
	ServerOpt mbstcp;
	// rpc
	ServerOpt rpc;
	// Websocket
	ServerOpt ws;
	MNOpt mns;
	DeviceOpt ocec;
	DeviceOpt metal;
	DeviceOpt ion;
	// 协议
	String protocol;
	// 格式
	String format;
	// 平台类型
	String type;
	// 日志输出开关
	bool log;
};
