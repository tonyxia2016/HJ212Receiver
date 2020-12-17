#pragma once
#include <type.h>
#include <boost/signals2.hpp>
typedef boost::signals2::connection connection;

// 空参数信号
typedef boost::signals2::signal<void()> sig_void0;

// 返回数据信号
typedef boost::signals2::signal<void(const String& payload)> sig_data;

// 数据缓存信号
typedef boost::signals2::signal<void(uint8* buffer, size_t buffer_size)> sig_buffer;
typedef sig_buffer::slot_type function_buffer;

typedef std::function<String(const uint8* buff, const size_t buff_size, const int32 timeout_ms)> function_rw;

// MQ数据推送
typedef boost::signals2::signal<void(const String& topic, int qos, const String& payload)> sig_pub;

// Redis数据
typedef boost::signals2::signal<void(const String& key, const String& val)> sig_set;
typedef boost::signals2::signal<void(const String& key, int32 seconds, const String& val)> sig_setex;
typedef boost::signals2::signal<void(const String& key, const String& field, const String& val)> sig_hset;

typedef boost::signals2::signal<void(const String& key, int32 seconds)> sig_expire;

typedef boost::signals2::signal<String(const String& key)> sig_get;

typedef boost::signals2::signal<StringArray(const String& pattern)> sig_keys;

typedef boost::signals2::signal<StringMap(const String& key)> sig_hgetall;

typedef boost::signals2::signal<String(const String& key, const String& field)> sig_hget;

typedef boost::signals2::signal<void(const String& key)> sig_del;

typedef boost::signals2::signal<void(const String& key, const String& field)> sig_hdel;

/************************************************************************/
/* 采集完成回调                                                          */
/************************************************************************/
typedef boost::signals2::signal<void(void* driver_ptr, int result)> signal_task;
// 回调类型
typedef signal_task::slot_type slot_task;

// 正常推送标识
typedef boost::signals2::signal<void(const bool bNormal)> signal_bool;
typedef signal_bool::slot_type slot_bool;


/************************************************************************/
/* 接收到订阅数据的回调                                                   */
/************************************************************************/
typedef boost::signals2::signal<
	void(const std::string& topic, const std::string& payload)> signal_msg;
// 回调类型
typedef signal_msg::slot_type slot_msg;

/************************************************************************/
/* 数据推送回调信息                                                      */
/************************************************************************/
typedef boost::signals2::signal<void(const std::string& record)> signal_data; // , const std::string last_time
// 回调类型
typedef signal_data::slot_type slot_data;

