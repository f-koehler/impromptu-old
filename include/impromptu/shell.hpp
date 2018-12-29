#ifndef IMPROMPTU_SHELL_HPP
#define IMPROMPTU_SHELL_HPP

#include <filesystem>
#include <string>

namespace impromptu {
std::string get_cwd();
std::string get_shell();
std::filesystem::path get_home_directory();
std::filesystem::path shorten_path(const std::filesystem::path &path);
} // namespace impromptu

#endif
