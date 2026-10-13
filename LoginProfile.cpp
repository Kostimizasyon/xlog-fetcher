#include "LoginProfile.h"

LoginProfile::LoginProfile(std::string_view username, std::string_view password) : username(username), password(password) {}

const std::string LoginProfile::get_password() const {
	return this->password;
}

const std::string LoginProfile::get_username() const {
	return this->username;
}
