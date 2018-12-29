#ifndef IMPROMPTU_VCS_HPP
#define IMPROMPTU_VCS_HPP

#include <cstdint>
#include <filesystem>

namespace impromptu {
enum VCS : std::uint8_t { VCS_NONE, VCS_GIT, VCS_HG };

std::tuple<VCS, std::filesystem::path> detect_vcs(std::filesystem::path path);
} // namespace impromptu

#endif
