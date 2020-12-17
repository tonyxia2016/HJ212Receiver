#pragma once
#include <type.h>
#include <my_log.h>
#include "Connection.h"
#include <set>
#include <Locker.h>
#include "net.h"


namespace network
{
	typedef std::set<ConnectionPtr> ConnectionPtrSet;
	class ConnectionManager : public my_log, public MgrInterface, public boost::noncopyable
	{
	public:
		ConnectionManager(sig_log& lg)
			: my_log(lg) {

		}
		~ConnectionManager() {

		}

		/// Add the specified connection to the manager and start it.
		void start(ConnectionPtr c) {
			WriteLocker locker(mutex_);
			connections_.insert(c);
			c->start(false);
		}

		/// Stop the specified connection.
		void stop(ConnectionPtr c) {
			WriteLocker locker(mutex_);
			connections_.erase(c);
			c->stop();
		}

		/// Stop all connections.
		void stop_all() {
			WriteLocker locker(mutex_);
			for (auto c : connections_)
				c->stop();
			connections_.clear();
		}

		ConnectionPtr find_one(const String& clientid) {
			WriteLocker locker(mutex_);
			for (auto c : connections_) {
				if (c->find_id(clientid)) {
					return c;
				}
			}
			return nullptr;
		}

		bool send_data(const String& clientid, const String& data) {
			ConnectionPtr ptr = find_one(clientid);
			if (ptr == nullptr) {
				EmitLog(warning, "站点[%s]没有活动的会话.", clientid.c_str());
				return false;
			}
			return ptr->write_data(data);
		}

		// 数据发送
		virtual bool write_data(const String& clientid, const String& req) override {
			return send_data(clientid, req);
		}

		void send_data(const String& data) {
			WriteLocker locker(mutex_);
			for (auto c : connections_) {
				c->write_data(data);
			}
		}

	private:
		ConnectionPtrSet connections_;
		RWMutex mutex_;
	};
}


