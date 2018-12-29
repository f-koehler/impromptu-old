#include "impromptu/shell.hpp"

#include <cstdlib>
#include <unistd.h>

namespace impromptu {
std::string get_cwd() {
    char path[4096];
    errno = 0;
    if (getcwd(path, 4096) == nullptr) {
        return std::string("");
    }
    return std::string(path);
}

std::string get_shell() {
    char buf[256];
    const auto path =
        std::filesystem::path("/proc") / std::to_string(getppid()) / "exe";
    readlink(path.c_str(), buf, 256);
    return std::filesystem::path(buf).filename().native();
}

std::filesystem::path get_home_directory() {
    return std::filesystem::path(std::getenv("HOME"));
}

std::filesystem::path shorten_path(const std::filesystem::path &path) {
    auto shortp = std::filesystem::relative(path, get_home_directory());
    if (*shortp.begin() == "..")
        return path;
    return "~" / shortp;
}
} // namespace impromptu
