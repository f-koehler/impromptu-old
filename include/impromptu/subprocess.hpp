#ifndef IMPROMPTU_SUBPROCESS_HPP
#define IMPROMPTU_SUBPROCESS_HPP

#include <cstdio>
#include <memory>
#include <sstream>

std::string check_output(const std::string &cmd) {
    char buffer[128];
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"),
                                                  pclose);
    std::ostringstream strm;
    while (std::fgets(buffer, 128, pipe.get()) != nullptr) {
        strm << buffer;
    }
    return strm.str();
}

#endif
