#include "impromptu/git.hpp"

#include <fstream>

namespace impromptu {
std::string GitRepository::_fetch_action() {
    // rebase actions
    static const std::string dirs1[] = {"rebase-apply", "rebase"};
    for (const auto &tmp : dirs1) {
        const auto tmp_dir = _git_dir / tmp;
        if (!std::filesystem::is_directory(tmp_dir))
            continue;
        if (std::filesystem::is_regular_file(tmp_dir / "rebasing"))
            return "rebase";
        if (std::filesystem::is_directory(tmp_dir / "applying"))
            return "am";
        return "am/rebase";
    }

    if (std::filesystem::is_regular_file(_git_dir / "rebase-merge/interactive"))
        return "rebase-i";
    if (std::filesystem::is_directory(_git_dir / "rebase-merge"))
        return "rebase-m";

    // merge actions
    if (std::filesystem::is_regular_file(_git_dir / "MERGE_HEAD"))
        return "merge";

    // bisect actions
    if (std::filesystem::is_regular_file(_git_dir / "BISECT_LOG"))
        return "bisect";

    // cherry-pick actions
    if (std::filesystem::is_regular_file(_git_dir / "CHERRY_PICK_HEAD")) {
        if (std::filesystem::is_directory(_git_dir / "sequencer"))
            return "cherry-seq";
        return "cherry";
    }

    if (std::filesystem::is_directory(_git_dir / "sequencer"))
        return "cherry-or-revert";

    return std::string();
}

std::string GitRepository::_fetch_ref_head() {
    std::string ref;
    std::ifstream strm((_git_dir / "HEAD").c_str());
    std::getline(strm, ref);
    strm.close();
    ref = ref.substr(6);
    return ref;
}

std::string GitRepository::_fetch_hash() {
    std::string hash;
    std::ifstream strm((_git_dir / _ref_head.get()).c_str());
    std::getline(strm, hash);
    strm.close();
    return hash;
}

std::string GitRepository::_fetch_branch() {
    std::filesystem::path path(_ref_head.get());
    std::filesystem::path branch;
    for (auto iter = ++(++path.begin()); iter != path.end(); ++iter) {
        branch /= *iter;
    }
    return branch.native();
}

GitRepository::GitRepository(const std::filesystem::path &path)
    : _path(path), _git_dir(path / ".git"),
      _action(std::bind(&GitRepository::_fetch_action, this)),
      _ref_head(std::bind(&GitRepository::_fetch_ref_head, this)),
      _hash(std::bind(&GitRepository::_fetch_hash, this)),
      _branch(std::bind(&GitRepository::_fetch_branch, this)) {}

std::string GitRepository::get_action() { return _action.get(); }
std::string GitRepository::get_hash() { return _hash.get(); }
std::string GitRepository::get_branch() { return _branch.get(); }
} // namespace impromptu
