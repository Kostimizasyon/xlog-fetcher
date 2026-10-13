#include "SystemWatcher.h"
#include <chrono>
#include <ctime>
#include <string>
#include <format>

int get_connection(std::string& response) {
    return 0;
}

const std::string get_time() {

    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm now_tm;

    localtime_r(&now_tm, &now_c);

    return std::format("{:02}:{:02}:{:02}", now_tm.tm_hour, now_tm.tm_min, now_tm.tm_sec);

}
