#pragma once
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>

#define JsonAddStr(node, name, val) node.AddMember(name, rapidjson::Value::StringRefType(val), doc.GetAllocator())
#define JsonAddStrCopy(node, name, val) node.AddMember(name, rapidjson::Value(val, doc.GetAllocator()), doc.GetAllocator())
#define JsonAddStrCopy2(node, name, val) node.AddMember(rapidjson::Value(name, doc.GetAllocator()), rapidjson::Value(val, doc.GetAllocator()), doc.GetAllocator())
#define JsonAddMem(node, name, val) node.AddMember(name, rapidjson::Value(val), doc.GetAllocator())
#define JsonAddMem2(node, name, val) node.AddMember(rapidjson::Value(name, doc.GetAllocator()), rapidjson::Value(val), doc.GetAllocator())
#define JsonAdd(node, name, member) node.AddMember(name, member, doc.GetAllocator())
#define JsonAdd2(node, name, member) node.AddMember(rapidjson::Value(name, doc.GetAllocator()), member, doc.GetAllocator())
#define JsonArrayAdd(arr, item) arr.PushBack(item, doc.GetAllocator());

#define JsonDEF_Doc(name) rapidjson::Document name(rapidjson::kObjectType)
#define JsonDEF_Object(name) rapidjson::Value name(rapidjson::kObjectType)
#define JsonDEF_Array(name) rapidjson::Value name(rapidjson::kArrayType)

#define Json_IsArray(node, name) (node.HasMember(name) && node[name].IsArray())
#define Json_IsObject(node, name) (node.HasMember(name) && node[name].IsObject())
#define Json_IsBool(node, name) (node.HasMember(name) && node[name].IsBool())
#define Json_IsString(node, name) (node.HasMember(name) && node[name].IsString())
#define Json_IsInt(node, name) (node.HasMember(name) && node[name].IsInt())
#define Json_IsUint(node, name) (node.HasMember(name) && node[name].IsUint())
#define Json_IsDouble(node, name) (node.HasMember(name) && node[name].IsDouble())

inline bool Json_GetBool(rapidjson::Value& val, const char* name, const bool def_val = false) {
	if (Json_IsBool(val, name)) return val[name].GetBool(); 
	return def_val;
}
inline double Json_GetDouble(rapidjson::Value& val, const char* name, const double def_val = 0) {
	if (Json_IsDouble(val, name)) return val[name].GetDouble();
	if (Json_IsInt(val, name)) return val[name].GetInt();
	if (Json_IsUint(val, name)) return val[name].GetUint();
	return def_val;
}
inline String Json_GetString(rapidjson::Value& val, const char* name, const char* def_val = "") {
	if (Json_IsString(val, name)) return val[name].GetString();
	return def_val;
}

inline String Json_toString(rapidjson::Value& node, const char* name, const char* def_val = "") {
	if (Json_IsDouble(node, name)) {
		return std::to_string(node[name].GetDouble());
	}
	if (Json_IsInt(node, name)) {
		return std::to_string(node[name].GetInt());
	}
	if (Json_IsString(node, name)) {
		return node[name].GetString();
	}
	return def_val;
}

inline String get_json_value(rapidjson::Value& val) {
	if (val.IsString()) {
		return val.GetString();
	}
	else if (val.IsUint()) {
		return std::to_string(val.GetUint());
	}
	return String();
};

inline String get_json_value(rapidjson::Value& val, const char* name) {
	String str;
	if (val.HasMember(name)) {
		str = get_json_value(val[name]);
	}
	return str;
};

template<typename T>
inline void get_json_value(T& _return, rapidjson::Value& val) {
	if (typeid(T) == typeid(uint32) || typeid(T) == typeid(int32))
	{
		if (val.IsString()) {
			_return = std::stoi(val.GetString());
		}
		else if (val.IsUint()) {
			_return = val.GetUint();
		}
	}
	else if (typeid(T) == typeid(float) || typeid(T) == typeid(double))
	{
		if (val.IsString()) {
			_return = std::stof(val.GetString());
		}
		else if (val.IsFloat()) {
			_return = val.GetFloat();
		}
		else if (val.IsDouble()) {
			_return = val.GetDouble();
		}
	}
};

template<typename T>
void get_json_obj_value(T& _return, rapidjson::Value& obj, const char* name) {
	auto iter = obj.FindMember(name);
	if (iter != obj.MemberEnd()) {
		get_json_value(_return, iter->value);
	}
};

inline String Json2Buffer(const rapidjson::Value& doc) {
	rapidjson::StringBuffer sb;
	rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
	doc.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
	return sb.GetString();
}

inline String Json2Buffer2(const rapidjson::Value& doc) {
	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
	doc.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
	return sb.GetString();
}