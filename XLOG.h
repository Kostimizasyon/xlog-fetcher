#pragma once

#include <string>
#include <string_view>
#include "httplib/httplib.h"

class LoginProfile;

class XLOG {
private:
	httplib::Client server;
public:
	XLOG(std::string_view url) : server(std::string(url)) {};
	int logout() const;
	int login(const LoginProfile& user) const;
	void keep_connection(const LoginProfile& user) const; 
};
