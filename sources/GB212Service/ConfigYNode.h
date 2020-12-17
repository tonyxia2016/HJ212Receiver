#pragma once
#include <yaml-cpp/yaml.h>
#include "cnfYNode.h"
#include "ConfigY.h"


namespace YAML {
	template<>
	struct convert<stMonitParam> {
		static Node encode(const stMonitParam& rhs) {
			Node node;
			ENSET(Id);
			ENSET(Name);
			ENSET(Unit);
			ENSET(OtId);
			ENSET(SlaveId);
			ENSET(ParamId);
			return node;
		}
		static bool decode(const Node& node, stMonitParam& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			DESET(Id, String, String());
			DESET(Name, String, String());
			DESET(Unit, String, String());
			DESET(OtId, String, String());
			DESET(SlaveId, int32, 0);
			DESET(ParamId, int32, 0);
			return true;
		}
	};
	template<>
	struct convert<stStationInfo> {
		static Node encode(const stStationInfo& rhs) {
			Node node;
			ENSET(sstation);
			ENSET(name);
			ENSET(stype);
			ENSET(ips);
			return node;
		}
		static bool decode(const Node& node, stStationInfo& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			DESET(sstation, String, String());
			DESET(name, String, String());
			DESET(stype, String, String());
			DESET(ips, String, String());
			return true;
		}
	};
	template<>
	struct convert<stNodeConfig> {
		static Node encode(const stNodeConfig& rhs) {
			Node node;
			node = convert<ConfigOpt>::encode(rhs);
			ENSET(factors);
			ENSET(stations);
			return node;
		}
		static bool decode(const Node& node, stNodeConfig& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			convert<ConfigOpt>::decode(node, rhs);
			DESET(factors, MonitParamArray, MonitParamArray());
			DESET(stations, stStationInfoArray, stStationInfoArray());
			return true;
		}
	};
}

