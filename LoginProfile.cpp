#include "LoginProfile.h"

LoginProfile::LoginProfile() = default;

LoginProfile::LoginProfile(std::string_view username, std::string_view password) : username(username), password(password) {}

const std::string LoginProfile::get_password() const {
	return this->password;
}

const std::string LoginProfile::get_username() const {
	return this->username;
}

void LoginProfile::set_password(std::string_view pass) {
	this->password = pass;
}

void LoginProfile::set_username(std::string_view name) {
	this->username = name;
}
