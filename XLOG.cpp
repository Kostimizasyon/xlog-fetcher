#include "XLOG.h"
#include "LoginProfile.h"
#include "json.hpp"

int XLOG::logoutFromAccount() //returns 0 if no active session and 1 if we logout sucesfully unconventional but kinda cool so fuck it
{

    if (const auto res = server.Get("/index.php?do=auth/logout")) {

        if (res->status == 200) {

            const nlohmann::json data = nlohmann::json::parse(res->body);

            if (data["message"].contains("Ba\u015far\u0131yla")) {
                std::cout << "Sucesfully logged out!\n";
                return 0;
            }
            else if (data["message"] == "Aktif bir oturumunuz bulunmamaktad\u0131r. L\u00fctfen sayfay\u0131 yenileyiniz") {
                std::cout << "No active session\n";
                return 1;
            }
            std::cout << "Error, error: " << data["message"].get<std::string>() << "\n";
            return -1;
        }
        std::cout << "Error, status code: " << std::to_string(res->status) << "\n";
        return -1;
    }
    std::cout << "Wrong link or smtn\n";
    return -1;

}

int XLOG::loginToAccount(const LoginProfile& user)
{

    const httplib::Params data = { {"entegration_type", "user_auth"}, {"username", user.getUsername() }, {"password", user.getPassword() }};

    if (const auto res = server.Post("/index.php?do=auth/auth", data))
    {

        if (res->status == 200) {

            const nlohmann::json data = nlohmann::json::parse(res->body);

            if (data["result"] == true) {
                std::cout << "Sucesfully logged in!\n";
                return 1;
            }
            else {
                std::cout << "Error, error: " << data["message"].get<std::string>() << "\n";
            }

        }
        else {
            std::cout << "Error, status code: " << std::to_string(res->status) << "\n";
        }

    }
    return -1;

}

