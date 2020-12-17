#include "DataMiddleware.h"
#include <json.h>

void DataMiddleware::set_ttl(const int32 ttl)
{
	ttl_ = ttl;
}

void DataMiddleware::set_type(const String& ptype)
{
	ptype_ = ptype;
}

void DataMiddleware::ReqRep(const ProtoRequest& req, ProtoResponse& res)
{
#if 1
	{
		std::lock_guard<std::mutex> lck(mtx_);
		FILE* f = fopen("./rx.log", "a+");
		if (f) {
			String ss = "[" + Math::Date::getnow() + "]\r\n" + req.body;
			if (req.body[req.body.size() - 1] != '\n') {
				ss += "\r\n";
			}
			fwrite(ss.data(), 1, ss.size(), f);
			fclose(f);
		}
	}
#endif
	// 将utf8转成gb2312(ascii)
	//String body = Math::Tools::from_utf8(req.body);
	const String& body = req.body;

	// parse gb212 format data
	GB212::GB212Array arr;
	GB212::Parser(arr, body);
	// 实时，最新，报文
	for (auto& i : arr) {
		if (i.valid()) {
			// 实时数据, 设置回复数据 , 推送
			if (i.is_data()) {
				task_real_data(i, res);
			}
			// 推送接收数据
			publish_package(req, i.full, i.data.MN, i.data.ST, emPackType::Data);
		}
		else {
			// 解析心跳数据
			task_heart_package(i, req, res);
		}
	}

}

void DataMiddleware::task_real_data(const GB212& gb, ProtoResponse& res)
{
	auto qn = gb.data.QN;
	auto cn = gb.data.CN;
	auto st = gb.data.ST;
	auto mn = gb.data.MN;
	auto DataTime = gb.data.CPs.DataTime;
	// 设置客户端ID
	res.Ids.emplace_back(mn);
	res.ST = st;
	// 设置消息回复
	if (gb.is_need_reply()) {
		res.bodys.emplace_back(gb.data_res("9014").toString());
	}
	// 获取数据段对象
	auto items = gb.data.CPs.Value;
	// 获取数据时间
	const String date1 = DataTime.substr(0, 8);
	const String date2 = DataTime.substr(8, 6);
	// 设置存储Redis的key
	const StringArray keyarr = { ("GB212_" + cn), st, mn, date1, date2 };
	const String key = Math::Tools::join(keyarr, ":");

	// 最新数据缓存
	const StringArray lastkeyarr = { ("0_last_gb212_" + cn), st, mn };
	const String lastkey = Math::Tools::join(lastkeyarr, ":");
	const StringMap lastKV = *signal_hgetall_(lastkey);

	// 遍历数据区
	JsonDEF_Doc(doc);
	JsonDEF_Object(jdata);
	for (auto& i : items) {
		// 是否需要更新数据
		bool is_update_last = true;
		// Redis存储的JSON对象
		JsonDEF_Doc(yinzi);
		const String& field = i.first;
		for (auto& j : i.second) {
			// 对于多参数的，组合成JSON数据
			JsonAddStrCopy2(yinzi, j.first.c_str(), j.second.c_str());
		}
		// 对于多参数的，组合成JSON数据存储
		const auto str = Json2Buffer(yinzi);
		signal_hset_(key, field, str);
		// 更新最新
		auto fi = lastKV.find(field);
		if (fi != lastKV.end()) {
			auto& lastv = fi->second;
			const auto ivs = Math::Tools::split(lastv, "|");
			if (lastv.size() > 14 && ivs.size() > 1 && ivs[0] > DataTime) {
				is_update_last = false;
			}
		}
		if (is_update_last) {
			signal_hset_(lastkey, field, DataTime + "|" + str);
		}
		// 将因子加入到数据中
		JsonAdd2(jdata, field.c_str(), yinzi);
	}
	// 设置Redis存储key的生命周期1天
	if (ttl_ != -1) {
		signal_expire_(key, ttl_);
	}

	// 转码base64
	const String& rx = gb.full;
// 	Uint8Array body(gb.full.begin(), gb.full.end());
// 	Math::Tools::base64_encode(&rx, body);

	// 构造推送对象
	const String topic = "/gb212/" + ptype_ + "/data/" + mn + "/" + st + "/" + cn;
	JsonAddStrCopy(doc, "Id", mn.c_str());
	JsonAddStrCopy(doc, "Type", cn.c_str());
	JsonAddStrCopy(doc, "Time", DataTime.c_str());
	JsonAdd(doc, "Datas", jdata);
	JsonAddStrCopy(doc, "Rx", rx.c_str());
	const String payload = Json2Buffer(doc);
	// 推送实时数据
	signal_pub_(topic, 1, payload);
}

void DataMiddleware::task_heart_package(const GB212& gb, const ProtoRequest& req, ProtoResponse& res)
{
	String id;
	auto i0 = gb.full.find("##");
	auto i00 = gb.full.find("MN=");
	// get mn
	size_t i1;
	if (i00 != String::npos) {
		i1 = gb.full.find(";", i00);
	}
	else {
		i1 = gb.full.find("\r\n", i0);
	}
	if (i00 != String::npos) {
		id = gb.full.substr(i00 + 3, i1 - i00 - 3);
	}
	else if (i0 != String::npos) {
		id = gb.full.substr(i0 + 2, i1 - i0 - 2);
	}
	// get st
	String st;
	size_t i2 = gb.full.find("ST=");
	size_t i21 = gb.full.find(";", i2);
	if (i2 != String::npos && i21 != String::npos) {
		st = gb.full.substr(i2 + 3, i21 - i2 - 3);
	}

	// 设置客户端ID
	if (id.size()) {
		res.Ids.emplace_back(id);
	}
	if (st.empty()) {
		st = req.ST;
	}
	// 推送报文信息
	publish_package(req, gb.full, id, st, emPackType::Heart);
}

void DataMiddleware::publish_package(const ProtoRequest& req, const String& body, const String& clientid, const String& st, const emPackType pack_type)
{
	const String Id = clientid.empty() ? "0" : clientid;
	const String topic = "/gb212/" + ptype_ + "/rx/" + Id;

	// 转码base64
 	String rx;
	rx = Math::Tools::to_utf8(body);
// 	Uint8Array buff(body.begin(), body.end());
// 	Math::Tools::base64_encode(&rx, buff);

	JsonDEF_Doc(doc);
	JsonAddStrCopy(doc, "Ip", req.address.c_str());
	JsonAddMem(doc, "Port", req.port);
	JsonAddStrCopy(doc, "Id", Id.c_str());
	JsonAddMem(doc, "Type", pack_type);
	JsonAddStrCopy(doc, "Body", rx.c_str());
	const String payload = Json2Buffer(doc);

	String DataTime = Math::Date::getnow("%04d%02d%02d%02d%02d%02d");
	const String date1 = DataTime.substr(0, 10);
	const String date2 = DataTime.substr(8);

	// redis key
	StringArray keyarr;
	if (clientid.size()) {
		keyarr = { "Z_RX_GB", st.empty() ? "00" : st, Id, date1 };
	}
	else {
		keyarr = { "Z_RX_GBUN", Id, date1 };
	}

	const String key = Math::Tools::join(keyarr, ":");
	signal_hset_(key, date2, payload);
	if (ttl_ != -1) {
		signal_expire_(key, ttl_);
	}

	// mqtt publish
	signal_pub_(topic, 0, payload);
}
