#pragma once
#include <string>

class LoginProfile {
private:
	std::string username;
	std::string password;
public:
	LoginProfile(std::string_view username, std::string_view password);

	const std::string get_username() const;
	const std::string get_password() const;

};
