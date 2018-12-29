#ifndef IMPROMPTU_GIT_HPP
#define IMPROMPTU_GIT_HPP

#include "subprocess.hpp"

#include <filesystem>
#include <iostream>

namespace impromptu {
/* std::string get_action(const std::filesystem::path& dir) { */
/*     if(std::filesystem::is_regular_file(dir / ".git" / "MERGE_HEAD")) { */
/*         return "merge"; */
/*     } */
/* } */

/* auto get_branch(const std::filesystem::path& dir) { */
/*     const auto symref = check_output("git -C " + dir.native() + "
 * symbolic-ref HEAD"); */

/*     return std::string(); */
/* } */

class GitRepository {
  private:
    const std::filesystem::path _path;
    const std::filesystem::path _git_dir;

    std::string _action;
    std::string _hash;
    std::string _branch;

  public:
    std::string _get_action() {
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

        if (std::filesystem::is_regular_file(_git_dir /
                                             "rebase-merge/interactive"))
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

    std::string _get_hash() {
        return check_output("git rev-parse --quiet --verify HEAD -C " +
                            _path.native());
    }

    std::string _get_branch() {
        std::filesystem::path path(
            check_output("git -C " + _path.native() + " symbolic-ref HEAD"));
        std::filesystem::path branch;
        for (auto iter = ++(++path.begin()); iter != path.end(); ++iter) {
            branch /= *iter;
        }
        return branch.native();
    }

  public:
    GitRepository(const std::filesystem::path &path)
        : _path(path), _git_dir(path / ".git"), _action(_get_action()),
          _hash(_get_hash()), _branch(_get_branch()) {}
};
} // namespace impromptu

#endif
