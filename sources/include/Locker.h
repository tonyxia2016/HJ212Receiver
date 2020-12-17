#pragma once
// ¶ÁĞ´Ëø
#include <boost/thread/thread.hpp>

typedef boost::shared_mutex RWMutex;
// ¶ÁËø
typedef boost::shared_lock<boost::shared_mutex> ReadLocker;
// Ğ´Ëø
typedef boost::unique_lock<boost::shared_mutex> WriteLocker;
