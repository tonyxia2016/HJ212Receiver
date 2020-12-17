#ifndef _XM_NEW_MBS_DEFINE_H_
#define _XM_NEW_MBS_DEFINE_H_

#define MBS_NUM(x) (x-1)

// 数据类型
enum RegisterType
{
	Coil			= MBS_NUM(1),
	DiscreteInput	= MBS_NUM(2),
	HoldingRegister = MBS_NUM(3),
	InputRegister	= MBS_NUM(4),
};

// Modbus功能码
enum FunctionCode {
	fInvalid = 0x00,
	ReadCoils = 0x01,
	ReadDiscreteInputs = 0x02,
	ReadHoldingRegisters = 0x03,
	ReadInputRegisters = 0x04,
	WriteSingleCoil = 0x05,
	WriteSingleRegister = 0x06,
	ReadExceptionStatus = 0x07,
	Diagnostics = 0x08,
	GetCommEventCounter = 0x0B,
	GetCommEventLog = 0x0C,
	WriteMultipleCoils = 0x0F,
	WriteMultipleRegisters = 0x10,
};

enum DODefine
{
	RunEnableBit		= MBS_NUM(1),
	ControlEnableBit	= MBS_NUM(2),
	ZeroStdBit			= MBS_NUM(3),
	CalibrateBit		= MBS_NUM(4),
	SO2Bit				= MBS_NUM(5),
	NOBit				= MBS_NUM(6),
	O3Bit				= MBS_NUM(7),
	COBit				= MBS_NUM(8),

};

enum AODefine
{
	MarkReg			= MBS_NUM(1),
	ModeReg			= MBS_NUM(2),
	Code32HReg		= MBS_NUM(3),
	Code32LReg		= MBS_NUM(4),
	PortNameReg		= MBS_NUM(5),
	BaudrateReg		= MBS_NUM(6),
	DatabitReg		= MBS_NUM(7),
	StopbitReg		= MBS_NUM(8),
	ParityReg		= MBS_NUM(9),
	FlowCtrlReg		= MBS_NUM(10),
	DTRReg			= MBS_NUM(11),
	RTSReg			= MBS_NUM(12),
	SampleRateReg	= MBS_NUM(13),
	BeginTimeReg	= MBS_NUM(15),
	BeforeTimeReg	= MBS_NUM(16),
	StableTimeReg	= MBS_NUM(17),
	AfterTimeReg	= MBS_NUM(18),
	GasConcReg		= MBS_NUM(19),
	GasFlowReg		= MBS_NUM(20),
};

enum DIDefine
{
	AlarmBit	= MBS_NUM(5),
};

enum AIDefine 
{
	DateBcdReg	= MBS_NUM(1),
	MonitorReg	= MBS_NUM(5),
	// 10个监测量内使用此
	StateReg10	= MBS_NUM(25),	// 5 + 10 * 2
	// 50个监测量内使用此
	StateReg50 = MBS_NUM(105),	// 5 + 50 * 2
	// 100个监测量内使用此
	StateReg100 = MBS_NUM(205),	// 5 + 100 * 2
	// 150个监测量内使用此
	StateReg150 = MBS_NUM(305),	// 5 + 150 * 2
	// 200个监测量内使用此
	StateReg200 = MBS_NUM(405),	// 5 + 200 * 2
};



#endif
