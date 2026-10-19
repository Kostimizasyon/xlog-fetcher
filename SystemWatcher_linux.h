#ifdef __linux__
#pragma once

#include <string>

class SystemWatcher {
public:
	int         get_connection(std::string& response);
	const std::string get_time();
};

#endif
