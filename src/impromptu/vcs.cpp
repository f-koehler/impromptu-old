#include "impromptu/vcs.hpp"

namespace impromptu {
std::tuple<VCS, std::filesystem::path> detect_vcs(std::filesystem::path path) {
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
