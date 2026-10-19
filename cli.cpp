#include <iostream>
#include <cstring>
#include "cli.h"


int match_arg(const char* arg)
{
    if (!strcmp(arg, "-lu") || !strcmp(arg, "--loginuser"))
        return LOGINUSER;
        
    if (!strcmp(arg, "-c") || !strcmp(arg, "--connect"))
        return CONNECT;

    if (!strcmp(arg, "-d") || !strcmp(arg, "--disconnect"))
        return DISCONNECT;

    if (!strcmp(arg, "-r") || !strcmp(arg, "--relog"))
        return RELOG;

    if (!strcmp(arg, "-h") || !strcmp(arg, "--help"))
        return HELP;

    if (!strcmp(arg, "-p") || !strcmp(arg, "--password"))
        return PASSWORD;

    if (!strcmp(arg, "-u") || !strcmp(arg, "--username"))
        return USERNAME;

    return ERROR;
}

void print_help() 
{
    std::cout << R"(Usage: ./xlog-fetcher [OPTIONS]

Session manager and credential authenticator with automated reconnect capabilities.

Options:
  -u, --username <USER>    Set username (creates or modifies .env automatically)
  -p, --password <PASS>    Set password (creates or modifies .env automatically)
  -lu,--loginuser <USER>:<PASS> login to xlog with the provided credentials
  -c, --connect            Connect using credentials from .env
  -d, --disconnect         Disconnect active session
  -r, --reconnect          Force a session reconnect
  -h, --help               Display this help text and exit

Notes:
  Providing -u or -p automatically creates or updates the local '.env' file;
  you do not need to create or edit the file manually.
)";
}
