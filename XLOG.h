#pragma once
#include "httplib.h"
#include <string>

class LoginProfile;

class XLOG {
private:
	httplib::Client server;
public:
	XLOG(std::string_view url) : server(std::string(url)) {};
	int logoutFromAccount();
	int loginToAccount(const LoginProfile& user);
};