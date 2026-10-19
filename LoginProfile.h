#pragma once
#include <string>

class LoginProfile {
private:
	std::string username;
	std::string password;
public:
	LoginProfile();
	LoginProfile(std::string_view username, std::string_view password);

	const std::string get_username() const;
	const std::string get_password() const;

	void set_username(std::string_view name);
	void set_password(std::string_view pass);
};
