#include "main-header.h"
#include <windows.h>
#include <iphlpapi.h>
#include <wininet.h>
#include <pdh.h>

#pragma comment(lib, "pdh.lib")

int main() {

    InternetWatcher watcher;
    XLOG server("http://192.168.100.1");
    const LoginProfile user("10634461634", "YURT123");

    int requestCount = 0;
    int attempt = 0;
    std::string response = "";

    while (true) {

        std::string_view comparison = response;

        int result = watcher.checkConnection(response);

        switch (result) {
            case -1:
            case 0:
                requestCount++;
                if (requestCount == 5) {
                    attempt++;
                    std::cout << "[" << watcher.getTime() << "] " << std::setw(15) << std::left << "Trying to login to XLOG, Attempt(" << attempt << ")\n";
                    int response = server.loginToAccount(user);
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
            std::cout << "[" << watcher.getTime() << "] " << std::setw(15) << std::left << response << "\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));

    }


}