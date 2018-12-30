#ifndef IMPROMPTU_GIT_HPP
#define IMPROMPTU_GIT_HPP

#include "on_demand.hpp"
#include "subprocess.hpp"

#include <filesystem>
#include <string>

namespace impromptu {

class GitRepository {
  private:
    const std::filesystem::path _path;
    const std::filesystem::path _git_dir;

    OnDemandValue<std::string> _action;
    OnDemandValue<std::string> _ref_head;
    OnDemandValue<std::string> _hash;
    OnDemandValue<std::string> _branch;

    std::string _fetch_action();
    std::string _fetch_ref_head();
    std::string _fetch_hash();
    std::string _fetch_branch();

  public:
    GitRepository(const std::filesystem::path &path);

    std::string get_action();
    std::string get_ref_head();
    std::string get_hash();
    std::string get_branch();
};
} // namespace impromptu

#endif
