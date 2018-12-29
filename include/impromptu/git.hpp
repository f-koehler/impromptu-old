#ifndef IMPROMPTU_GIT_HPP
#define IMPROMPTU_GIT_HPP

#include "subprocess.hpp"

#include <string>
#include <filesystem>

namespace impromptu {

class GitRepository {
  private:
    const std::filesystem::path _path;
    const std::filesystem::path _git_dir;

    std::string _action;
    std::string _hash;
    std::string _branch;

  public:
    std::string _get_action();
    std::string _get_hash();
    std::string _get_branch();

  public:
    GitRepository(const std::filesystem::path &path);
};
} // namespace impromptu

#endif
