#ifndef IMPROMPTU_VCS_HPP
#define IMPROMPTU_VCS_HPP

#include <cstdint>
#include <filesystem>

namespace impromptu {
enum VCS : std::uint8_t { VCS_NONE, VCS_GIT, VCS_HG };

auto detect_vcs(std::filesystem::path path) {
    std::filesystem::path vcs_path;

    while (true) {
        if (!path.has_root_path())
            return std::make_tuple(VCS_NONE, path);

        vcs_path = path / ".git";
        if (std::filesystem::is_directory(vcs_path))
            return std::make_tuple(VCS_GIT, path);

        vcs_path = path / ".hg";
        if (std::filesystem::is_directory(vcs_path))
            return std::make_tuple(VCS_HG, path);

        path = path.parent_path();
    }
}
} // namespace impromptu

#endif
