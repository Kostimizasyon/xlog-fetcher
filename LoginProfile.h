#pragma once

#include <string>
#include <string_view>

class LoginProfile {
private:
	std::string username;
	std::string password;
public:
	LoginProfile(std::string_view username, std::string_view password);

	const std::string& getUsername() const;
	const std::string& getPassword() const;
};