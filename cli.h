#define CONNECT 1
#define DISCONNECT 2
#define RELOG 3
#define HELP 4
#define USERNAME 5
#define PASSWORD 6
#define LOGINUSER 7
#define KEEP 8
#define ERROR -1

int match_arg(const char* arg);

void print_help();
