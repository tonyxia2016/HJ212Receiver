#pragma once

#include <type.h>

/**
* 数据的标记状态
*/
enum class DataMark {
	N = 0,		// 正常采样数据
	B = 1,		// 运行不良,仪器存在报警时激活
	BB = 2,		// 连接不良,数采启动后一直没与仪器通信成功时激活
	W = 3,		// 等待数据恢复,与仪器通信成功后在超过数据生成周期还未正常时被激活
	H = 4,		// 有效数据不足
	HSp = 5,	// 数据超上限
	LSp = 6,	// 数据超下限
	PZ = 7,		// 零点检查(走零)
	PS = 8,		// 跨度检查(走标)
	AS = 9,		// 精度检查
	CZ = 10,	// 零点校准(校零)
	CS = 11,	// 跨度校准(校准)
	Re = 12,	// 仪器回补的数据带的标记
	ZNi = 15,	// 零点噪声
	SNi = 16,	// 量程噪声
	IEr = 17,	// 示值误差
	RPD = 18,	// 量程精密度
	DZS = 19,	// 24h零点漂移和量程漂移
	TSL = 30,	// 多点校准
	UNKNOWN = 40	// 其他
};

// 标记位转换函数
static DataMark covertMark(String strMark)
{
	DataMark res = DataMark::N;
	if ("N" == strMark)
	{
		res = DataMark::N;
	}
	else if ("B" == strMark)
	{
		res = DataMark::B;
	}
	else if ("BB" == strMark)
	{
		res = DataMark::BB;
	}
	else if ("W" == strMark) {
		res = DataMark::W;
	} 
	else if ("H" == strMark) {
		res = DataMark::H;
	}
	else if ("HSp" == strMark) {
		res = DataMark::HSp;
	}
	else if ("LSp" == strMark) {
		res = DataMark::LSp;
	}
	else if ("PZ" == strMark) {
		res = DataMark::PZ;
	}
	else if ("PS" == strMark) {
		res = DataMark::PS;
	}
	else if ("AS" == strMark) {
		res = DataMark::AS;
	}
	else if ("CZ" == strMark) {
		res = DataMark::CZ;
	}
	else if ("CS" == strMark) {
		res = DataMark::CS;
	}
	else if ("Re" == strMark) {
		res = DataMark::Re;
	}
	else if ("ZNi" == strMark) {
		res = DataMark::ZNi;
	}
	else if ("SNi" == strMark) {
		res = DataMark::SNi;
	}
	else if ("IEr" == strMark) {
		res = DataMark::IEr;
	}
	else if ("RPD" == strMark) {
		res = DataMark::RPD;
	}
	else if ("DZS" == strMark) {
		res = DataMark::DZS;
	}
	else if ("TSL" == strMark) {
		res = DataMark::TSL;
	}
	else {
		res = DataMark::UNKNOWN;
	}
	
	return res;
}