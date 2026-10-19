#ifdef __linux__

#include "SystemWatcher_linux.h"
#include <string>
#include <NetworkManager.h>
#include <chrono>

int SystemWatcher::get_connection(std::string& response)
{
    static NMClient* client = nullptr;
    GError* error = nullptr;

    if (!client) {
        client = nm_client_new(nullptr, &error);
        if (!client) {
            response = error ? error->message : "Failed to connect to NetworkManager";
            if (error) g_error_free(error);
            return -1;
        }
    }

    // Forces an actual connectivity probe (blocking)
    NMConnectivityState state = nm_client_check_connectivity(client, nullptr, &error);
    if (error) {
        response = error->message;
        g_error_free(error);
        return -1;
    }

    switch (state) {
    case NM_CONNECTIVITY_FULL:
        response = "Connected";
        return 1;
    case NM_CONNECTIVITY_PORTAL:
        response = "Captive portal (login required)";
        return 0;
    case NM_CONNECTIVITY_LIMITED:
        response = "Network up, no internet";
        return 0;
    case NM_CONNECTIVITY_NONE:
        response = "No network";
        return 0;
    default:
        response = "Connectivity unknown (is connectivity checking enabled?)";
        return -1;
    }
}

const std::string SystemWatcher::get_time() {

    std::time_t now_c = std::time(nullptr);
    std::tm now_tm;
    localtime_r(&now_c, &now_tm);
    return std::format("{:02}:{:02}:{:02}", now_tm.tm_hour, now_tm.tm_min, now_tm.tm_sec);

}

#endif
