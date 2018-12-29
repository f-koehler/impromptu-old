#ifndef IMPROMPTU_SHELL_HPP
#define IMPROMPTU_SHELL_HPP

#include <cstdlib>
#include <filesystem>
#include <string>

#include <unistd.h>

namespace impromptu {
auto get_cwd() {
    char path[4096];
    errno = 0;
    if (getcwd(path, 4096) == nullptr) {
        return std::string("");
    }
    return std::string(path);
}

auto get_shell() {
    char buf[256];
    const auto path =
        std::filesystem::path("/proc") / std::to_string(getppid()) / "exe";
    readlink(path.c_str(), buf, 256);
    return std::filesystem::path(buf).filename().native();
}

auto get_home_directory() { return std::filesystem::path(std::getenv("HOME")); }

auto shorten_path(const std::filesystem::path &path) {
    auto shortp = std::filesystem::relative(path, get_home_directory());
    if (*shortp.begin() == "..")
        return path;
    return "~" / shortp;
}

} // namespace impromptu

#endif
