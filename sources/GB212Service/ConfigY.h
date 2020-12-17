#pragma once
#include "cnfY.h"
#include <yaml-cpp/yaml.h>

#define ENSETINT(name) node[#name] = (int32)rhs.name
#define ENSET(name) node[#name] = rhs.name
#define DESETINT(name, type, def) rhs.name = node[#name].IsDefined() ? static_cast<type>(node[#name].as<int32>()) : def
#define DESET(name, type, def) rhs.name = node[#name].IsDefined() ? node[#name].as<type>() : def
#define ENSET2(name, name2) node[#name] = rhs.name2
#define DESET2(name, name2, type, def) rhs.name2 = node[#name].IsDefined() ? node[#name].as<type>() : def

namespace YAML {
	template<>
	struct convert<TopicOpt> {
		static Node encode(const TopicOpt& rhs) {
			Node node;
			ENSET(topic);
			ENSET(qos);
			return node;
		}
		static bool decode(const Node& node, TopicOpt& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			DESET(topic, String, "");
			DESET(qos, int32, 0);
			return true;
		}
	};
	template<>
	struct convert<MQTTConnOpt> {
		static Node encode(const MQTTConnOpt& rhs) {
			Node node;
			ENSET(id);
			ENSET(type);
			ENSET(host);
			ENSET(port);
			ENSET(user);
			ENSET(password);
			ENSET(clientid);
			ENSET(clean);
			ENSET(enable);
			ENSET(subtops);
			return node;
		}
		static bool decode(const Node& node, MQTTConnOpt& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			DESET(id, int32, 1);
			DESET(type, String, "all");
			DESET(host, String, "localhost");
			DESET(port, int32, 1883);
			DESET(user, String, "");
			DESET(password, String, "");
			DESET(clientid, String, "");
			DESET(clean, bool, true);
			DESET(enable, bool, true);
			DESET(subtops, TopicMap, TopicMap());
			return true;
		}
	};
	template<>
	struct convert<SQLConnOpt> {
		static Node encode(const SQLConnOpt& rhs) {
			Node node;
			ENSET(enable);
			ENSET(type);
			ENSET(host);
			ENSET(port);
			ENSET(user);
			ENSET(password);
			ENSET(database);
			ENSET(stationsql);
			return node;
		}
		static bool decode(const Node& node, SQLConnOpt& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			DESET(enable, bool, true);
			DESET(type, String, "mssql");
			DESET(host, String, "mssql");
			DESET(port, int32, 1433);
			DESET(user, String, "sa");
			DESET(password, String, "");
			DESET(database, String, "master");
			DESET(stationsql, String, "");
			return true;
		}
	};
	template<>
	struct convert<RedisConnOpt> {
		static Node encode(const RedisConnOpt& rhs) {
			Node node;
			ENSET(enable);
			ENSET(host);
			ENSET(port);
			ENSET(password);
			ENSET(index);
			ENSET(ttl);
			return node;
		}
		static bool decode(const Node& node, RedisConnOpt& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			DESET(enable, bool, true);
			DESET(host, String, "127.0.0.1");
			DESET(port, int32, 6379);
			DESET(password, String, "");
			DESET(index, int32, 0);
			DESET(ttl, int32, -1);
			return true;
		}
	};
	template<>
	struct convert<TaskTimeOpt> {
		static Node encode(const TaskTimeOpt& rhs) {
			Node node;
			ENSET(day);
			ENSET(hour);
			ENSET(fminute);
			ENSET(minute);
			ENSET(real);
			ENSET(state);
			ENSET(env);
			ENSET(qc);
			ENSET(alarm);
			return node;
		}
		static bool decode(const Node& node, TaskTimeOpt& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			DESET(day, int32, 0);
			DESET(hour, int32, 0);
			DESET(fminute, int32, 0);
			DESET(minute, int32, 0);
			DESET(real, int32, 0);
			DESET(state, int32, 0);
			DESET(env, int32, 0);
			DESET(qc, int32, 0);
			DESET(alarm, int32, 0);
			return true;
		}
	};
	template<>
	struct convert<ServerOpt> {
		static Node encode(const ServerOpt& rhs) {
			Node node;
			ENSET(enable);
			ENSET(host);
			ENSET(port);
			return node;
		}
		static bool decode(const Node& node, ServerOpt& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			DESET(enable, bool, false);
			DESET(host, String, "127.0.0.1");
			DESET(port, int32, 6001);
			return true;
		}
	};
	template<>
	struct convert<MNOpt> {
		static Node encode(const MNOpt& rhs) {
			Node node;
			ENSET(metal);
			ENSET(ocec);
			ENSET(ion);
			return node;
		}
		static bool decode(const Node& node, MNOpt& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			DESET(metal, String, "88888880000001");
			DESET(ocec, String, "88888880000002");
			DESET(ion, String, "88888880000003");
			return true;
		}
	};
	template<>
	struct convert<DeviceOpt> {
		static Node encode(const DeviceOpt& rhs) {
			Node node;
			ENSET(mn);
			ENSET(cn);
			return node;
		}
		static bool decode(const Node& node, DeviceOpt& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			DESET(mn, String, "");
			DESET(cn, String, "");

			return true;
		}
	};
	template<>
	struct convert<ConfigOpt> {
		static Node encode(const ConfigOpt& rhs) {
			Node node;
			ENSET(mqtt);
			ENSET(sqldb);
			ENSET(redis);
			ENSET(times);
			ENSET(tcp);
			ENSET(mbstcp);
			ENSET(rpc);
			ENSET(ws);
			ENSET(mns);
			ENSET(ocec);
			ENSET(protocol);
			ENSET(format);
			ENSET(type);
			ENSET(log);
			return node;
		}
		static bool decode(const Node& node, ConfigOpt& rhs) {
			if (!node.IsMap()) {
				return false;
			}
			DESET(mqtt, MQTTConnOptArray, MQTTConnOptArray());
			DESET(sqldb, SQLConnOpt, SQLConnOpt());
			DESET(redis, RedisConnOpt, RedisConnOpt());
			DESET(times, TaskTimeOpt, TaskTimeOpt());
			DESET(tcp, ServerOpt, ServerOpt());
			DESET(mbstcp, ServerOpt, ServerOpt());
			DESET(rpc, ServerOpt, ServerOpt());
			DESET(ws, ServerOpt, ServerOpt());
			DESET(mns, MNOpt, MNOpt());
			DESET(ocec, DeviceOpt, DeviceOpt());
			DESET(metal, DeviceOpt, DeviceOpt());
			DESET(ion, DeviceOpt, DeviceOpt());
			DESET(protocol, String, String());
			DESET(format, String, String());
			DESET(type, String, String());
			DESET(log, bool, false);
			return true;
		}
	};
}


