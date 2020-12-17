#ifndef _XM_DATA_FORAMT_DEFINE_H_
#define _XM_DATA_FORAMT_DEFINE_H_
#include "type_def.h"


/************************************************************************/
/* 设备类型ID                                                            */
/************************************************************************/
enum class DeviceType {
	ignore = 0,
	SO2 = 1,
	NO = 2,
	CO = 3,
	O3 = 4,
	PM10 = 5,
	PM25 = 6,
	PM10_25 = 7,
	PM1 = 8,
	TSP = 9,
	QX = 10,	// 大气气象
	VIS = 11,	// 能见度
	CALI = 12,	// 校准仪
	ZERO = 13,	// 零气机
	H2S = 14,	// 硫化氢
	ATM = 15,	// 黑炭仪
	INM = 16,	// 浊度仪
	ASAS = 17,	// 粒径谱仪
	NOy = 18,	// NOy
	NH3 = 19,	// NH3
	GHG = 20,	// 温室气体
	ATPS = 21,	// 大气稳定度
	VOC = 22,	// VOCs
	CTRL = 23,	// 控制模块
	UVRM = 24,	// UV辐射计
	CEILO = 25,		// 云高仪
	ENV = 26,		// 站房管理
	OCEC = 27,		// OCEC
	MYMT = 28,		// 重金属
	SOCA = 29,		// 可溶性离子
	SPHM = 30,		// 太阳光度计
	CH4 = 32,		// 甲烷
	QXEX = 101,		// 气象综合
	PAN = 102,		// PAN
	GJGP = 103,		// 光解光谱
	C = 105,		// 炭黑

};


inline bool is_have_act(const DeviceType dt) {
	return (dt == DeviceType::SO2 || dt == DeviceType::NO || dt == DeviceType::CO || dt == DeviceType::O3 ||
		dt == DeviceType::PM10 || dt == DeviceType::PM25 || dt == DeviceType::PM10_25 || dt == DeviceType::PM1 || dt == DeviceType::TSP);
}

inline bool is_have_two(const DeviceType dt) {
	return is_have_act(dt) || dt == DeviceType::VOC;
}

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
	PA = 31,	// 精密度审核
	PF = 40,	// 颗粒物-流量检查
	PME = 41,	// 颗粒物-膜片检查
	PT = 42,	// 颗粒物-温度压力检查
	PCS = 43,	// 颗粒物-清洗采样头
	OT = 50,	// 自定义标记
};

inline String mark2Str(const DataMark mark){
	switch (mark) {
	case DataMark::N:
		return "N";
	case DataMark::B:
		return "B";
	case DataMark::BB:
		return "BB";
	case DataMark::W:
		return "W";
	case DataMark::H:
		return "H";
	case DataMark::HSp:
		return "HSp";
	case DataMark::LSp:
		return "LSp";
	case DataMark::PZ:
		return "PZ";
	case DataMark::PS:
		return "PS";
	case DataMark::AS:
		return "AS";
	case DataMark::CZ:
		return "CZ";
	case DataMark::CS:
		return "CS";
	case DataMark::Re:
		return "Re";
	case DataMark::ZNi:
		return "ZNi";
	case DataMark::SNi:
		return "SNi";
	case DataMark::IEr:
		return "IEr";
	case DataMark::RPD:
		return "RPD";
	case DataMark::DZS:
		return "DZS";
	case DataMark::TSL:
		return "TSL";
	case DataMark::PA:
		return "PA";
	case DataMark::PF:
		return "PF";
	case DataMark::PME:
		return "PME";
	case DataMark::PT:
		return "PT";
	case DataMark::PCS:
		return "PCS";
	case DataMark::OT:
		return "OT";
	default:
		break;
	}
	return "N";
}

/************************************************************************/
/* 设备运行状况                                                          */
/************************************************************************/
enum class RunState {
	NotRun = 0,		// 任务未运行
	Normal,			// 一切正常
	NotOpen,		// 未连接
	NotResponse,	// 无响应
	InvalidData,	// 无效的数据
	InvalidDriver,	// 无效的驱动，未加载
	DataNotUpdate,	// 数据未更新
};

// 设备输出数据状态
enum class DeviceOutputState {
	UnKnown = 0,	// 默认标况
	Standard = 1,	// 标准状况
	Actual = 2,		// 实际状况
	QxActual = 6,	// 气象计算
};

/**
* 监测仪器参数的类型
* RealTime实时数据; State状态量; Alarm报警量
*/
enum class ParamterType {
	RealTime = 1,	// 实时数据
	State = 2,		// 状态数据
	Alarm = 3,		// 报警数据
};


/************************************************************************/
/* 参数的key                                                            */
/************************************************************************/
struct ParamterKey {
	ParamterKey(const ParamterType t, int d) :type(t), id(d){}
	ParamterKey(int t, int d) :ParamterKey(static_cast<ParamterType>(t), d) {}
	bool operator<(const ParamterKey& o) const{
		return (this->type < o.type) || ((this->type == o.type) && (this->id < o.id));
	}
	ParamterType type;	// 参数类型
	int id;				// 参数ID
};


/************************************************************************/
/* 参数数据                                                          */
/************************************************************************/
struct  ParamterValue
{
	ParamterValue(float value) :val(value){}
	union 
	{
		float	val;	// 设备的数据
		int32	ival = 0;
	};
	
};
// 设备参数的map结构
typedef std::map<ParamterKey, ParamterValue> DeviceParamterMap;


/**
* 监测仪器参数
*/
struct ParamterInfo {
	std::string	param_name;
	std::string	param_unit;
	std::string	value_min;
	std::string	value_max;
	bool	hint = false;
	int		point_num = 0;
	int critical_time = 0;
	int sub_show = 0;
	int state_key = 0;
	std::string state_desc;
};


/************************************************************************/
/* 设备类型参数对象名称                                                   */
/************************************************************************/
typedef std::map<DeviceType, std::map<int, ParamterInfo>> DeviceTypeParamObj;


/************************************************************************/
/*  设备识别key                                                          */
/************************************************************************/
struct DriverKey
{
	DriverKey() :code("00000000"), number(0){}
	DriverKey(const std::string& code, int number) :code(code), number(number){}
	DriverKey(const DeviceType type, int number) : number(number) {
		char str[10];
		std::sprintf(str, "0000%02d00", type);
		this->code = str;
	}
	DriverKey(const int type, int number) : DriverKey(static_cast<DeviceType>(type), number) {}
	DriverKey(const char* code, int number) :code(code), number(number){}
	bool operator<(const DriverKey& o)const{
		return (this->code < o.code) || ((this->code == o.code) && (this->number < o.number));
	}
	int id() const {
		return DriverKey::id(type(), number);
	}
	static inline int id(int type, int number) {
		return ((number << 8) & 0xFF00) | (type & 0xFF);
	}
	int type() const {
		if (code.size() < 8)
			return 0;
		return std::stoi(code, 0, 16) >> 8 & 0xFF;
	}
	const char* operator()() const {
		return code.c_str();
	}
	std::string	code;	// 设备的32位编码
	int			number;	// 同类型的实例ID号
};

typedef std::vector<DriverKey> DriverKeyArray;


/**
* 类型实例码
*/
struct TypeKey {
	TypeKey(){}
	TypeKey(int t, int n) : type(static_cast<DeviceType>(t)), number(n){}
	bool operator<(const TypeKey& o)const{
		return (this->type < o.type) || ((this->type == o.type) && (this->number < o.number));
	}
	DeviceType type = DeviceType::SO2;	// 设备类型
	int number = 0;			// 实例化的数量
};
typedef std::vector<TypeKey> TypeKeyArray;

/**
* 查询的数据类型
*/
enum QueryType {
	Second,
	OneMinute,
	FiveMinute,
	OneHour,
	OrigHour,
	OneDay,
};


// 报警数据结构
struct AlarmItem {
	AlarmItem(const DriverKey& k, const ParamterKey& p) : key(k),pkey(p), happen_date(), resume_date(), confirm_date(){}
	DriverKey key;
	ParamterKey pkey;
	std::string happen_date;
	double happen_value = 0;
	int8 overrun_type = 0;
//	bool is_overrun_critical = false;
	bool resumed = false;
	std::string resume_date;
	double resume_value = 0;
	bool confirm = false;
	std::string confirm_date;
};
typedef std::vector<AlarmItem> AlarmItemArray;

// 报警数据描述结构
struct AlarmDetailItem {
	std::string DeviceCode;
	int DeviceNumber = 0;
	std::string DeviceTypeName;
	std::string DeviceManuName;
	std::string DeviceModelName;
	ParamterType pType;
	std::string pName;
	std::string happen_date;
	double happen_value = 0;
	int8 overrun_type = 0;
	bool resumed = false;
	std::string resume_date;
	double resume_value = 0;
	bool confirm = false;
	std::string confirm_date;
};
typedef std::vector<AlarmDetailItem> AlarmDetailItemArray;


/************************************************************************/
/*  设备参数                                                             */
/************************************************************************/
struct DeviceValue 
{
	DeviceValue(){}
	DeviceValue(const DriverKey& key) :key(key){}
	DriverKey			key;			// 设备驱动标识码
	std::string			timestamp_str;	// 数据采集的时间，字符串
	std::string			mark;			// 数据的标识信息
	DeviceParamterMap	paramter;		// 设备参数数据
};


/**
* 监测仪器参数集合
*/
struct DeviceInfo{
	int	type_slave = 0;
	std::string	type_id;
	std::string	type_name;
	int type_used = 0;

	std::string	manu_id;
	std::string	manu_name;
	std::string	manu_code;

	std::string	dev_code;
	int	dev_number = 0;
	std::string	dev_model;

	std::map<int, ParamterInfo> real;
	std::map<int, ParamterInfo> state;
	std::map<int, ParamterInfo> alarm;
};

/**
 * 颗粒物仪器的压力和温度                                                                      
*/
struct PTState 
{
	PTState() { memset(this,0,sizeof(*this)); }
	int Pid;	// 压力对应的id号
	int Tid;	// 温度对应的id号
	char Punit[20]; // 压力输出单位
	char Tunit[20]; // 温度输出单位
};
// 设备的压力温度状态信息
typedef std::map<std::string, PTState> DevicePTState;


/************************************************************************/
/* 数据查询记录                                                          */
/************************************************************************/
typedef std::map<int, double> ItemData;
#define NULL_VALUE -1001
#define DEFMARK		""
struct QueryItemData 
{
	QueryItemData() 
		: date(), PM10(NULL_VALUE), PM25(NULL_VALUE), SO2(NULL_VALUE), CO(NULL_VALUE), O3(NULL_VALUE), VIS(NULL_VALUE)
		, PM10_mark(DEFMARK), PM25_mark(DEFMARK)
		, SO2_mark(DEFMARK), NO_mark(DEFMARK), CO_mark(DEFMARK), O3_mark(DEFMARK)
		, QX_mark(DEFMARK), VIS_mark(DEFMARK), ENV_mark(DEFMARK) {
		NO.insert(std::make_pair(1, NULL_VALUE));
		NO.insert(std::make_pair(2, NULL_VALUE));
		NO.insert(std::make_pair(3, NULL_VALUE));
		QX.insert(std::make_pair(1, NULL_VALUE));
		QX.insert(std::make_pair(2, NULL_VALUE));
		QX.insert(std::make_pair(3, NULL_VALUE));
		QX.insert(std::make_pair(4, NULL_VALUE));
		QX.insert(std::make_pair(5, NULL_VALUE));
		QX.insert(std::make_pair(6, NULL_VALUE));
		QX.insert(std::make_pair(7, NULL_VALUE));
		ENV.insert(std::make_pair(1, NULL_VALUE));
		ENV.insert(std::make_pair(2, NULL_VALUE));
	}
	QueryItemData(const std::string& d) 
		: date(d), PM10(NULL_VALUE), PM25(NULL_VALUE), SO2(NULL_VALUE), CO(NULL_VALUE), O3(NULL_VALUE), VIS(NULL_VALUE)
		, PM10_mark(DEFMARK), PM25_mark(DEFMARK)
		, SO2_mark(DEFMARK), NO_mark(DEFMARK), CO_mark(DEFMARK), O3_mark(DEFMARK)
		, QX_mark(DEFMARK), VIS_mark(DEFMARK), ENV_mark(DEFMARK) {
		NO.insert(std::make_pair(1, NULL_VALUE));
		NO.insert(std::make_pair(2, NULL_VALUE));
		NO.insert(std::make_pair(3, NULL_VALUE));
		QX.insert(std::make_pair(1, NULL_VALUE));
		QX.insert(std::make_pair(2, NULL_VALUE));
		QX.insert(std::make_pair(3, NULL_VALUE));
		QX.insert(std::make_pair(4, NULL_VALUE));
		QX.insert(std::make_pair(5, NULL_VALUE));
		QX.insert(std::make_pair(6, NULL_VALUE));
		QX.insert(std::make_pair(7, NULL_VALUE));
		ENV.insert(std::make_pair(1, NULL_VALUE));
		ENV.insert(std::make_pair(2, NULL_VALUE));
	}
	std::string date;
	double PM10;
	double PM25;
	double SO2;
	ItemData NO;
	double CO;
	double O3;
	ItemData QX;
	double VIS;
	ItemData ENV;
	// 数据标记
	std::string PM10_mark;
	std::string PM25_mark;
	std::string SO2_mark;
	std::string NO_mark;
	std::string CO_mark;
	std::string O3_mark;
	std::string QX_mark;
	std::string VIS_mark;
	std::string ENV_mark;
};

// 单一参数数据记录
struct QueryOneItem 
{
	QueryOneItem() :date(), mark(DEFMARK), samples(0) {}
	QueryOneItem(const std::string& d):date(d),mark(DEFMARK), samples(0) {}
	std::string date;
	std::string mark;
	int32 samples;
	ItemData data;
};


#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
/************************************************************************/
/* 消息主题                                                                     */
/************************************************************************/
class MessageTopic
{
public:
	MessageTopic() :province(), city(), area(), stationCode(), dataType(), devType(), devDataType(), reserve()
	{

	}
	MessageTopic(const std::string& in) 
	{
		std::vector<std::string> result;
		boost::split(result, in, boost::is_any_of("/"), boost::token_compress_off);
		if (result.size())
		{
			try {
				int iPos = 0;
				if (result.at(0).empty()){
					iPos = 1;
				}
				province = result.at(iPos++);
				city = result.at(iPos++);
				area = result.at(iPos++);
				stationCode = result.at(iPos++);
				dataType = result.at(iPos++);
				devType = result.at(iPos++);
				devDataType = result.at(iPos++);
				reserve = result.at(iPos++);
			}
			catch (std::exception&) {

			}
		}
	}
	std::string out(bool has_header = true)
	{
		return (has_header ? ("/" + province) : province) + "/" + city + "/" + area +"/" + stationCode
			+"/" + dataType  +"/" + devType  +"/" + devDataType + "/" + reserve;
	}

	std::string		province;	// （hubei）
	std::string 	city;		// (xiaogan)
	std::string 	area;		// (xiaonan)
	std::string		type;		// 站点类型(EAMS, SEAMS)
	std::string 	stationCode;	// (SS420984099)
	std::string 	dataType;	// (仪器的数据，日志数据，提醒数据)
	std::string 	devType;	// (all, SO2, NO, CO)
	std::string 	devDataType;	// (小时，分钟，秒钟)
	std::string 	reserve;	// 保留
};


/************************************************************************/
/* 控制的控制操作                                                        */
/************************************************************************/
enum ControlOperation
{
	ControlStd = 0x0100,
	ControlCalStd = 0x0101,
	ControlZero = 0x0200,
	ControlCalZero = 0201,
};

enum ControlObject
{
	ObjectZero = 0,
	ObjectSO2 = 1,
	ObjectNOx = 2,
	ObjectO3 = 3,
	ObjectCO = 4,
};

/**
* 几种质控任务类型
*/
enum ControlTask {
	ZeroCheck = 0,				// 零点检查
	ZeroCalibrate,				// 零点校准
	SpanCheck,					// 跨度检查
	SpanCalibrate,				// 跨度校准
	ZeroNoise = 13,				// 零点噪声
	SpanNoise,					// 量程噪声
	IndicationError,			// 示值误差
	RangePrecisionDeviation,	// 量程精密度
	Drift24hZeroSpan,			// 24h零点漂移和24h量程漂移
	MultiPonitCalibrate,		// 多点校准
	PrecisionAudit,				// 精密度审核
};

enum class ControlDataType {
	TotalTask = 0,		// 总体任务
	ZeroCheck,			// 零点检查
	SpanCheck,			// 跨度检查
	ZeroNoise,			// 零点噪声
	SpanNoise,			// 量程噪声
	Indication,			// 示值误差
	IndicationZero,		// 示值误差0
	Precision20,		// 20%量程精密度
	Precision80,		// 80%量程精密度
	Drift24hZero,		// 24小时零点漂移
	Drift24hSpan20,		// 24小时20%量程漂移
	Drift24hSpan80,		// 24小时80%量程漂移
	MultiPointSpan,		// 多点校准
	PrecisionAuditZero,	// 精密度审核0
	PrecisionAudit,		// 精密度审核
};

enum class ControlResult {
	TaskInvalid = 0,	// 任务无效
	DataInvalid = 1,	// 数据无效
	Unqualified = 2,	// 不合格
	Qualified = 3,		// 合格
	Waiting = 10,		// 等待中,定时任务
	Running = 11,		// 正在进行中
	Finished = 12,		// 完成的
	Canceled = 13,		// 被取消的
	Timeout = 14,		// 超时的
};

/**
* 质控任务的参数
*/
struct ControlTaskParam {
	float FullRange = 500;			// 满量程浓度值,一般为500ppb
	int GasFlow = 5000;				// 流量,一般为5000ml
	int ConcPercent = 80;			// 标气浓度百分比,默认为80%
	int ZeroStableTime = 5;			// 通零气达到稳定的时间(分钟)
	int Span10PerStableTime = 15;	// 通10%浓度标准气体到达稳定的时间(分钟)
	int Span20PerStableTime = 15;	// 通20%浓度标准气体到达稳定的时间(分钟)
	int Span40PerStableTime = 15;	// 通40%浓度标准气体到达稳定的时间(分钟)
	int Span50PerStableTime = 15;	// 通50%浓度标准气体到达稳定的时间(分钟)
	int Span60PerStableTime = 15;	// 通60%浓度标准气体到达稳定的时间(分钟)
	int Span80PerStableTime = 15;	// 通80%浓度标准气体到达稳定的时间(分钟)
	int ReserveStableTime = 15;		// 通入气体到达稳定的时间(分钟)(保留项)
	int ExperimentNumber = 3;		// 进行实验的次数
	int ResumeSampleTime = 2;		// 结束后恢复到采样稳定的时间(分钟)
};


	
struct ControlParam 
{
	ControlParam():begin_time(1), before_time(3), stable_time(30), after_time(2)
	, conc(400), flow(5000){}
	int begin_time = 1;		// 准备时间,秒
	int before_time = 3;		// 质控前处理时间,秒
	int stable_time = 15;	// 质控过程时间,分钟
	int after_time = 2;		// 质控后处理时间,秒
	int conc = 400;				// 通气浓度,单位ppb,CO(ppm)
	int flow = 5000;			// 通气流量,单位ml
};

/************************************************************************/
/* 定时控制任务的记录状态                                                 */
/************************************************************************/
enum class TaskTimerState {
	Waiting = 0,
	Finished = 1,
	Timeout = 2,
	Canceled = 3,
};

/************************************************************************/
/* 定时任务的参数                                                         */
/************************************************************************/
struct TaskTimerItem 
{
	int uid = 0;
	DeviceType type;
	int number = 0;
	ControlTask task;
	std::string date;
};
typedef std::vector<TaskTimerItem> TaskTimerList;


/**
* 配置驱动控制参数
* 采集频率, 推送的主题和QOS, 质控相应的时间
*/
struct DriverControlConfig{
	ControlParam zero;				// 走零
	ControlParam zeroCal;			// 教零
	ControlParam span;				// 走标
	ControlParam spanCal;			// 教标
};



/************************************************************************/
/* 控制过程中的错误                                                       */
/************************************************************************/
enum ControlError
{
	ControlFinished,
	ControlModuleError = 1,
	DynamicGenerateGasError			= 0x1001,
	AnalyticalChangeNoSample		= 0x1002, 
	DynamicStopGenerateGasError		= 0x1004,
	AnalyticalResumeSample			= 0x1008,
};


// 质控的结果
struct QCTaskResult{
	float val = 0;			// 子任务的计算结果
	ControlResult rc;		// 子任务的符合结果
};

// 每个质控任务的子任务
struct QCTaskProcess{
	std::map<std::string,float> processData;	// 子任务的过程数据
	std::vector<QCTaskResult> result;			// 子任务的结果集
};

// 质控任务的参数
struct QCTaskItem{
	std::string code;
	int32 number = 0;		// 设备类型实例
	DeviceType devType;		// 设备类型
	int32 envTaskType;		// 任务类型[网络1,现场2,计划3,4手工]
	ControlTask qcType;		// 质控类型
	std::string startDate;	// 开始时间
	std::string endDate;		// 结束时间
	int32 completedCount = 0;	// 完成次数
	std::map<int32,QCTaskProcess> data;	// 子任务的列表数据, <子任务序号,过程数据>
	ControlResult state;	//任务状态
	ControlTaskParam param;	// 参数
	int32 uid = 0;	// 记录标识
};
typedef std::vector<QCTaskItem> QualityControlTask;

struct QualityTaskDataItem 
{
	// tb_task_data(devType INT,number INT,qcType INT,date VARCHAR(20),stdValue float,actValue float)
	DeviceType devType;
	int number;
	ControlTask qcType;
	ControlDataType qcDataType;
	std::string date;
	double stdValue;
	double actValue;
};
typedef std::vector<QualityTaskDataItem> QualityTaskData;


// 选取的数据点
struct StablePoint {
	double stdval;	// 设定值
	double val;		// 监测值
	string datetime; // 数据时间点
};
// 添加手动质控的参数
struct ManualQCParam {
	DeviceType devType;	// 设备类型
	ControlTask qcType;	// 质控类型
	string startDate;	// 开始时间
	string endDate;		// 结束时间
	std::vector<StablePoint> point;
};

// 设备运行状态
struct DevRunStatus 
{
	DriverKey key;
	bool run = false;
	RunState state;
};

// 设备运行状态
struct DeviceStatus : public DevRunStatus
{
	std::string			date;
	std::string			mark;
	std::map<int32, double>	real;		// 设备参数数据
};
typedef std::vector<DeviceStatus> DeviceStatusArray;

// 站点运行状态
struct NodeStatus
{
	bool StoreReal;
	bool StoreMinute;
	bool StoreHour;
	DeviceStatusArray row;
};


// 秒钟数据-只包含监测值
struct QuerySecondItem
{
	std::string date;
	std::string mark;
	std::map<int32, double>  data;
};


// 回补数据格式
typedef std::map<std::string, std::map<int32, double>> HistoryData;

// 用户权限表
enum AuthorityLevel {
	None = 0,
	ROOT = 1,
	Admin,
	Users,
};

struct User {
	int32 UserId;
	std::string UserName;
	std::string UserPasswd;
	AuthorityLevel level;
	bool Freeze;
};

// 授权类型
enum AuthorityType {
	unknown = 0,	// 未知状态
	Trial = 1,		// 软件试用期
	License			// license文件授权
};

// 软件授权信息
struct AuthorityInfo {
	AuthorityType type;
	std::string code;
	std::string pccode;
	std::string install_date;
	std::string license_date;
	int32 license_days;
	bool is_authority;
};

// 上传XML文件配置
struct StationConfig {
	StationConfig() {
		memset(this, 0, sizeof(*this));
	}
	std::string sender;
	std::string cityname;
	std::string citycode;
	std::string districtname;
	std::string districtcode;
	std::string stationname;
	std::string stationcode;
	std::string stationattribute;
	std::string longitude;
	std::string latitude;
	std::string admincode;
	std::string timetype;
	std::string timecode;
	bool enable;		// 是否启用
	std::string dir;		// 输出目录
};


// 异常信息
struct ExceptionContext
{
	ExceptionContext():code(0), str() {}
	ExceptionContext(int32 c,const std::string& s):code(c),str(s) {}
	ExceptionContext(const std::string& s):code(0),str(s) {}
	int32 code;
	std::string str;
};

// 手动标记记录
struct ManualMark
{
	int id;				// 记录ID
	int type;			// 标记类型 1为手动标记,2为定时标记
	DeviceType devType;	// 设备类型
	DataMark oldMark;	// 标记前
	DataMark newMark;	// 标记后
	DataMark renewMark;	// 恢复后
	String startDate;	// 标记日期
	String endDate;		// 结束日期
	String code32;		// 设备编码
	String content;		// 备注信息
};
typedef std::vector<ManualMark> ManualMarkArray;


// 定时预标记
struct TimeMarkItem 
{
	int32 tid;
	DeviceType devType;	// 设备类型
	DataMark newMark;	// 标记类型
	string startDate;	// 开始时间
	string endDate;		// 结束时间
	string content;		// 说明信息
};
typedef std::vector<TimeMarkItem> TimeMarkArray;


/**
* 传输参数描述
*/
struct TransferParamDesc {
	TransferParamDesc() :pk(ParamterType::RealTime,0){}
	TypeKey tk;		// 设备
	ParamterKey pk;	// 参数
	string name;	// 名称
	string format;	// 数据格式
};
typedef std::vector<TransferParamDesc> TransferParamDescArray;


#endif
