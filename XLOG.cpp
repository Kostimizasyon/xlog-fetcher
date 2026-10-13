#include "XLOG.h"
#include "LoginProfile.h"
#include "httplib/httplib.h"
#include "json/json.hpp"

int XLOG::logout() const //returns 0 if no active session and 1 if we logout sucesfully unconventional but kinda cool so fuck it
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

int XLOG::login(const LoginProfile& user) const
{

    const httplib::Params data = { {"entegration_type", "user_auth"}, {"username", user.get_username() }, {"password", user.get_password() }};

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

void XLOG::keep_connection(const LoginProfile& user) const 
{

    int requestCount = 0;
    int attempt = 0;
    std::string response = "";

    while (true) {

        std::string_view comparison = response;

        const int result = SystemWatcher::get_connection(response);

        switch (result) {
        case -1:
            std::cout << "Error something idk";
            break;
        case 0:
            requestCount++;
            if (requestCount == 5) {
                attempt++;
                std::cout << "[" << SystemWatcher::getTime() << "] " << std::setw(15) << std::left << "Trying to login to XLOG, Attempt(" << attempt << ")\n";
                const int response = XLOG::login(user);
                if (response != 1) {
                    requestCount = 0;
                }
            }
            break;
        case 1:
            requestCount = 0;
            attempt = 0;
            break;
        }

        if (comparison != response) {
            std::cout << "[" << SystemWatcher::getTime() << "] " << std::setw(15) << std::left << response << "\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));

    }

}

