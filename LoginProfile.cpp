#include "LoginProfile.h"

LoginProfile::LoginProfile(std::string_view username, std::string_view password) : username(username), password(password) {}

const std::string&  LoginProfile::getUsername() const
{
	return username;
}

const std::string& LoginProfile::getPassword() const
{
	return password;
}