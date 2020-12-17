#pragma once
#include <map>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

// 定义类型名称
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef char	int8;
typedef short	int16;
typedef int		int32;
#ifdef _WIN32
typedef unsigned __int64	uint64;
typedef __int64	int64;
#else
typedef unsigned long long	uint64;
typedef long long	int64;
#endif

typedef uint8	u8;
typedef uint16	u16;
typedef uint32	u32;
typedef uint64	u64;
typedef int8	i8;
typedef int16	i16;
typedef int32	i32;
typedef int64	i64;

// 数组
typedef std::vector<std::string> StringArray;
typedef std::list<std::string> StringList;
typedef std::vector<int8> ByteArray;
typedef std::map<std::string, std::string> StringMap;
typedef std::string	String;

typedef std::function<bool(const char* topic, const char* payload, int payload_size, int qos)> publish_handler;
typedef std::function<void(const char* topic, const char* payload, int payload_size, int sid)> subscribe_handler;

#include <thread>
typedef std::thread Thread;

#include <chrono>
// 休眠毫秒
#define msleep(millsec) std::this_thread::sleep_for(std::chrono::milliseconds(millsec));
// 休眠秒
#define ssleep(sec) std::this_thread::sleep_for(std::chrono::seconds(sec));

// 请求回调
typedef std::function<bool(const String& req, String& res)> parser_handler;
// 推送回调
typedef std::function<bool(const char* topic, const char* payload, int payload_size, int qos)> publish_handler;
// 日志信息
typedef std::function<void(const string file, const string func, int32 line, int32 level, const string str)> log_handler;

// 异常等级
enum LogLevel
{
	elDebug,
	elInfo,
	elWarn,
	elError,
	elQc = 8,
	elSample,
};
// #define WriteLog(level, str) if(log_) log_(__FILE__,__FUNCTION__,__LINE__,level,str)
// #define WriteLogPtr(p, level, str) if(p&&p->log_) p->log_(__FILE__,__FUNCTION__,__LINE__,level,str)

// 操作系统类型
// #if defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
// 
// #elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
// #  if defined(WINAPI_FAMILY)
// #  else
// #    define M_OS_WIN32
// #  endif
// 
// #elif defined(__sun) || defined(sun)
// 
// #endif
// 
// #if defined(M_OS_WIN32) || defined(M_OS_WIN64) || defined(M_OS_WINRT)
// #  define M_OS_WIN
// #endif
// 
// #if defined(M_OS_WIN)
// #  undef M_OS_UNIX
// #elif !defined(M_OS_UNIX)
// #  define M_OS_UNIX
// #endif


// 获取16位数据的高8位
#define GET16H(d)		((d)>>8&0xff)
// 获取16位数据的低8位
#define GET16L(d)		((d)&0xff)
// 通过高低8位构造16位数据
#define GET16T(h,l)		(((h)<<8&0xff00)|((l)&0xff))
// 交换16位数据的高低8位获取数据
#define GET16S(d)		GET16T(GET16L(d),GET16H(d))
// 获取32位数据的高16位
#define GET32H(d)		((d)>>16&0xffff)
// 获取32位数据的低16位
#define GET32L(d)		((d)&0xffff)


// 安全释放指针
#define ReleasePtr(w) if(w!=nullptr){delete w; w=nullptr;}
#define DeletePtr(w) if(w!=nullptr){delete w;}


#define CLASS_DISABLE_COPY(Class) \
    Class(const Class &) = delete;\
    Class &operator=(const Class &) = delete;


template <typename T> static inline T *qGetPtrHelper(T *ptr) { return ptr; }
template <typename Wrapper> static inline typename Wrapper::pointer qGetPtrHelper(const Wrapper &p) { return p.data(); }

#define M_DECLARE_PRIVATE(Class) \
    inline Class##Private* d_func() { return reinterpret_cast<Class##Private *>(qGetPtrHelper(d_ptr)); } \
    inline const Class##Private* d_func() const { return reinterpret_cast<const Class##Private *>(qGetPtrHelper(d_ptr)); } \
    friend class Class##Private;

#define M_DECLARE_PRIVATE_D(Dptr, Class) \
    inline Class##Private* d_func() { return reinterpret_cast<Class##Private *>(qGetPtrHelper(Dptr)); } \
    inline const Class##Private* d_func() const { return reinterpret_cast<const Class##Private *>(qGetPtrHelper(Dptr)); } \
    friend class Class##Private;

#define M_DECLARE_PUBLIC(Class)                                    \
    inline Class* q_func() { return static_cast<Class *>(q_ptr); } \
    inline const Class* q_func() const { return static_cast<const Class *>(q_ptr); } \
    friend class Class;

#define M_D(Class) Class##Private * const d = d_func()
#define M_Q(Class) Class * const q = q_func()

