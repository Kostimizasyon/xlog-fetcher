#pragma once

#ifdef __linux__
#include "SystemWatcher_linux.h"
#elif _WIN32
#include "SystemWatcher_win.h"
#endif

#include "httplib/httplib.h"

class LoginProfile;

class XLOG {
private:
	httplib::Client server;
	SystemWatcher watcher;
public:
	XLOG(std::string_view url) : server(std::string(url)) {};
	int logout();
	int login(const LoginProfile& user);
	int relog(const LoginProfile& user);
	void keep_connection(const LoginProfile& user); 
};
