#ifdef _WIN32

#include <string>
#include <iostream>
#include <string>
#include <netlistmgr.h>

class SystemWatcher {
private:
	NLM_CONNECTIVITY connectivity = NLM_CONNECTIVITY_DISCONNECTED;
	INetworkListManager* pNLM = NULL;
	HRESULT hr = 0;
public:
	SystemWatcher();
	int         get_connection(std::string& response);
	const std::string get_time();
	~SystemWatcher();
};

#endif
