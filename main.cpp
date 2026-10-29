#include "XLOG.h"
#include "cli.h"
#include "LoginProfile.h"
#include "env.h"

#include "cdotenv/cdotenv_extended.h"

int main(int argc, char** argv)
{
    LoginProfile user{};
    int res;

    if (argc == 1) {
        res = KEEP;
    }
    else if (argc >= 4) {
        std::cerr << "Bad args, -h for help \n";
        return -1;
    }
    else {
        res = match_arg(argv[1]);   // flag is always argv[1]

        if (res == HELP) {
            print_help();
            return 0;
        }

        // flags that need a value: -u <user>, -p <pass>, -lu <user:pass>
        if (res == USERNAME || res == PASSWORD || res == LOGINUSER) {
            if (argc != 3) {
                std::cerr << "Missing value for " << argv[1] << ". Use --help.\n";
                return -1;
            }

            if (res == USERNAME || res == PASSWORD) {
                const char* key = (res == PASSWORD) ? "PASSWORD" : "USERNAME";
                if (replace_env(key, argv[2], ENV_PATH) != SUCESS) {
                    res = write_env(key, argv[2],ENV_PATH,NULL);
                    if ( res != SUCESS) {
                        std::cerr << "Error writing .env file \n";
                        return -1;
                    }
                }
                std::cout << "Sucesfully set " << key << "!" << '\n';
                return 0;
            }

            // LOGINUSER: "USERNAME:PASSWORD"
            std::string creds = argv[2];
            auto pos = creds.find(':');   // first ':' only, so passwords may contain ':'
            if (pos == std::string::npos || pos == 0 || pos == creds.size() - 1) {
                std::cerr << "Expected format USERNAME:PASSWORD\n";
                return -1;
            }

            user.set_username(creds.substr(0, pos));
            user.set_password(creds.substr(pos + 1));
        }
    }

    if (res != LOGINUSER) {
        read_env(ENV_PATH);

        const char* env_user = std::getenv("USERNAME");
        const char* env_pass = std::getenv("PASSWORD");

        if (!env_user || !env_pass) {
            std::cerr << "Error: Required credentials are not set.\n";
            if (!env_user) std::cerr << "  - USERNAME is missing from environment / .env\n";
            if (!env_pass) std::cerr << "  - PASSWORD is missing from environment / .env\n";
            std::cerr << "Run with '-u <user>' and '-p <pass>' to set them, or configure your '.env' file.\n";
            return -1;
        }

        user.set_username(env_user);
        user.set_password(env_pass);
    }

    XLOG server("http://192.168.1.1");

    switch (res) {
        case STATS:
            server.get_usage();
	    break;
        case CONNECT:
        case LOGINUSER:
            server.login(user);
            break;
        case DISCONNECT:
            server.logout();
            break;
        case RELOG:
            server.relog(user);
            break;
        default:
            server.keep_connection(user);
            break;
    }

    return 0;
}


