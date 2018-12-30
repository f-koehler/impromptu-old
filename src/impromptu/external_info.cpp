#include "impromptu/external_info.hpp"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <string>

namespace impromptu {
ExternalInfo::ExternalInfo(int argc, const char *argv[]) {
    exit_code = 0;
    number_of_jobs = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        if (arg == "-r") {
            ++i;
            if (i >= argc)
                break;
            exit_code = std::atoi(argv[i]);
            continue;
        }

        if (arg == "-j") {
            ++i;
            if (i >= argc)
                break;
            const auto len = strlen(argv[i]);
            if (len == 0)
                break;
            number_of_jobs = std::count(argv[i], argv[i] + len, '\n') + 1;
        }
    }
}
} // namespace impromptu
