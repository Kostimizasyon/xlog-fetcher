#include "InternetWatcher.h"
#include <iostream>
#include <string>
#include <chrono>

InternetWatcher::InternetWatcher() {
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
}

int InternetWatcher::checkConnection(std::string& response) {

    hr = CoCreateInstance(CLSID_NetworkListManager, NULL, CLSCTX_ALL, IID_INetworkListManager, (void**)&pNLM);

    if (!SUCCEEDED(hr)) {
        return -1;
    }
        // THE "BETTER" LINE: Ask the manager directly for the machine's global state
        hr = pNLM->GetConnectivity(&connectivity);

        if (!SUCCEEDED(hr)) {
            return -1;
        }

        // Check if ANY internet bit is flipped on (IPv4 or IPv6)
        bool hasInternet = (connectivity & NLM_CONNECTIVITY_IPV4_INTERNET) || (connectivity & NLM_CONNECTIVITY_IPV6_INTERNET);

        // Check if we are totally disconnected
        bool isDisconnected = (connectivity == NLM_CONNECTIVITY_DISCONNECTED);

        // Check if we are JUST on a local network (No internet)
        bool localOnly = (connectivity & NLM_CONNECTIVITY_IPV4_NOTRAFFIC) || (connectivity & NLM_CONNECTIVITY_IPV6_NOTRAFFIC) && !hasInternet;

        if (localOnly) {
            response = "Yes but no internet";
            return 0;
        }
        else if (isDisconnected) {
            response = "No intenret";
            return -1;
        }
        else {
            response = "Yes internet";
            return 1;
        }
}

std::string InternetWatcher::getTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    
    std::tm now_tm;
    localtime_s(&now_tm, &now_c); // This uses Windows' local clock settings

    return std::format("{:02}:{:02}:{:02}", now_tm.tm_hour, now_tm.tm_min, now_tm.tm_sec);
}

InternetWatcher::~InternetWatcher() {
	pNLM->Release();
	CoUninitialize();
}