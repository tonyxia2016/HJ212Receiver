#pragma once
#include <type.h>
#include <func.h>
#include <deque>
#include <boost/circular_buffer.hpp>

namespace RMQ
{
	enum { max_buffer_size = 4096 };
	typedef std::deque<Uint8Array> DataQueue;

	struct ReceiveData
	{
		// 缓存数据
		char buf[max_buffer_size];
		// 数据长度
		size_t bufsize = 0;
		// 数据时间
		time_t t = 0;

		ReceiveData() {
			memset(buf, 0, sizeof(buf));
		}

		// insert
		void insert(const char* buffer, const size_t size) {
			if (buffer && size > 0) {
				bufsize = size > max_buffer_size ? max_buffer_size : size;
				memcpy(this->buf, buffer, bufsize);
				this->t = Math::Timer::now_ms();
			}
		}

		inline size_t size() const {
			return bufsize;
		}
		inline const char* data() const {
			return buf;
		}
	};
	typedef boost::circular_buffer<ReceiveData> ReceiveBuffer;
}