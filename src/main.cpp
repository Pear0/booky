#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>

#include "SQLiteCpp/SQLiteCpp.h"

#include "Storage.h"

const char *shell_functions_str =
#include "shell_functions.sh"
;

std::string get_home() {
    const char *home_dir;

    if ((home_dir = getenv("HOME")) == nullptr) {
        home_dir = getpwuid(getuid())->pw_dir;
    }

    return std::string(home_dir);
}

int main(int argc, const char **argv) {
    std::cout << "Hello, World!" << std::endl;

    auto home = get_home();

    auto our_dir = home + "/.booky";

    if (mkdir(our_dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
        if (errno != EEXIST) {
            // something else
            std::cout << "cannot create '~/.booky':" << strerror(errno) << std::endl;
            throw std::runtime_error(strerror(errno));
        }
    }

    auto db_file = our_dir + "/data.db";
    Storage storage(db_file.c_str());

    if (argc == 1) {
        std::cout << "TODO: help here\n";
        return 1;
    }

    std::string command(argv[1]);

    if (command == "shell-init") {
        std::cout << shell_functions_str << std::endl;
        return 0;
    }

    if (!getenv("SHELL_EVALED")) {
        std::cerr << "Flag not set! Did you change your init script?" << std::endl;
    }


    if (command == "shell-init") {
        std::cout << shell_functions_str << std::endl;
        return 0;
    }




    auto value = storage.getPath("test");
    if (value) {
        std::cout << *value << std::endl;
    } else {
        std::cout << "No bookmark named test!" << std::endl;
    }

    return 0;
}