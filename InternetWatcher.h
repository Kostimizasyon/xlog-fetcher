#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <ondemandconnroutehelper.h>
#include <netlistmgr.h>
#include <string>

class InternetWatcher {
private:
	NLM_CONNECTIVITY connectivity = NLM_CONNECTIVITY_DISCONNECTED;
	INetworkListManager* pNLM = NULL;
	HRESULT hr = 0;
public:
	InternetWatcher();
	int checkConnection(std::string& responseMessage);
	std::string getTime();
	~InternetWatcher();
};