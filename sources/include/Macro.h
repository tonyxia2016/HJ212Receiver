#ifndef _XM_NEW_MACRO_H_
#define _XM_NEW_MACRO_H_

#define macroStr(s) #s

// 获取16位数据的高8位
#define GET16H(d)		((d)>>8&0xff)
// 获取16位数据的低8位
#define GET16L(d)		((d)&0xff)
// 通过高低8位构造16位数据
#define GET16T(h,l)		(((h)<<8&0xff00)|((l)&0xff))
// 交换16位数据的高低8位获取数据
#define GET16S(d)		GET16T(GET16L(d),GET16H(d))

#define GET32H(d)		((d)>>16&0xffff)
#define GET32L(d)		((d)&0xffff)


// 获取变量名称
#define VAR(w) #w

// 获取当前分钟值
#define Minute(a) a % 3600 / 60
// 获取当前分钟的时间戳
#define MinuteTime(a) a / 60 * 60

// 日志设置信息
#define WriteLog(level, str) log(MODULE_NAME,__FUNCTION__,__LINE__,level,str)

// 日志等级
enum LogLevel1
{
	LDEBUG = 1,
	LINFO,
	LWARN,
	LERROR,
	LQC = 8,
	LSAMPLE,
};

#endif