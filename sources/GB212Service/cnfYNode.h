#pragma once
#include "cnfY.h"

// ��������Ϣ
struct stMonitParam {
	stMonitParam& operator=(const stMonitParam& rhs) {
		if (this != &rhs) {
			OPEQ(Id);
			OPEQ(Name);
			OPEQ(Unit);
			OPEQ(OtId);
			OPEQ(SlaveId);
			OPEQ(ParamId);
		}
		return *this;
	}
	String	Id;		// ������ʶ
	String	Name;	// ��������
	String	Unit;	// ������λ
	String	OtId;	// ������ʶ
	int32	SlaveId = 0;	// ������Ӧ����վ�豸����
	int32	ParamId = 0;	// ������Ӧ����վ����id
};
typedef std::vector<stMonitParam> MonitParamArray;

// վ�����Ϣ
struct stStationInfo {
	String sstation;	// վ�����
	String name;		// վ������
	String stype;		// վ������
	String ips;			// վ��ip��ַ
};
typedef std::vector<stStationInfo> stStationInfoArray;

// ������������Ϣ
struct stNodeConfig : public ConfigOpt {
	stNodeConfig& operator=(const stNodeConfig& rhs) {
		if (this != &rhs) {
			ConfigOpt::operator=(rhs);
			OPEQ(factors);
			OPEQ(stations);
		}
		return *this;
	}
	// ������Ӷ�Ӧ��ϵ
	MonitParamArray factors;
	// ������Ӷ�Ӧ��ϵ
	stStationInfoArray stations;
};
