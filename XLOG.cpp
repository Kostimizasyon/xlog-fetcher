#include "XLOG.h"
#include "LoginProfile.h"
#include "httplib/httplib.h"
#include "json/json.hpp"

int XLOG::logout() // 1 = logged out, 0 = no active session, -1 = error
{
    std::cout << "Logging out... \n";

    const auto res = server.Get("/index.php?do=auth/logout");
    if (!res) {
        std::cerr << "Request failed: " << httplib::to_string(res.error()) << "\n";
        return -1;
    }
    if (res->status != 200) {
        std::cerr << "Error, status code: " << res->status << "\n";
        return -1;
    }

    const auto json = nlohmann::json::parse(res->body, nullptr, false);
    if (json.is_discarded() || !json.contains("message") || !json["message"].is_string()) {
        std::cerr << "Unexpected response from server\n";
        return -1;
    }

    const std::string msg = json["message"].get<std::string>();

    if (msg.find("Ba\u015far\u0131yla") != std::string::npos) {
        std::cout << "Successfully logged out!\n";
        return 1;
    }
    if (msg == "Aktif bir oturumunuz bulunmamaktad\u0131r. L\u00fctfen sayfay\u0131 yenileyiniz") {
        std::cout << "No active session\n";
        return 0;
    }

    std::cerr << "Error: " << msg << "\n";
    return -1;
}

int XLOG::login(const LoginProfile& user) // 1 = logged in, -1 = error
{
    std::cout << "Logging in... \n";

    const httplib::Params params = {
        {"entegration_type", "user_auth"},
        {"username", user.get_username()},
        {"password", user.get_password()}
    };

    const auto res = server.Post("/index.php?do=auth/auth", params);
    if (!res) {
        std::cerr << "Request failed: " << httplib::to_string(res.error()) << "\n";
        return -1;
    }
    if (res->status != 200) {
        std::cerr << "Error, status code: " << res->status << "\n";
        return -1;
    }

    const auto json = nlohmann::json::parse(res->body, nullptr, false);
    if (json.is_discarded() || !json.contains("result")) {
        std::cerr << "Unexpected response from server\n";
        return -1;
    }

    if (json["result"] == true) {
        std::cout << "Successfully logged in!\n";
        return 1;
    }

    if (json.contains("message") && json["message"].is_string())
        std::cerr << "Error: " << json["message"].get<std::string>() << "\n";
    else
        std::cerr << "Login failed\n";
    return -1;
}


int XLOG::relog(const LoginProfile& user)
{
    int ret = XLOG::logout();
    
    if (ret == -1) {
        return -1;
    }

    ret = XLOG::login(user);

    if (ret == -1) {
        return -1;
    }
    return 1;
}

void XLOG::keep_connection(const LoginProfile& user)
{

    int requestCount = 0;
    int attempt = 0;
    std::string response = "";

    while (true) {

        std::string_view comparison = response;

        const int result = watcher.get_connection(response);

        switch (result) {
        case -1:
            std::cout << "Error something idk";
            break;
        case 0:
            requestCount++;
            if (requestCount == 5) {
                attempt++;
                std::cout << "[" << watcher.get_time() << "] " << std::setw(15) << std::left << "Trying to login to XLOG, Attempt(" << attempt << ")\n";
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
            std::cout << "[" << watcher.get_time() << "] " << std::setw(15) << std::left << response << "\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));

    }

}
