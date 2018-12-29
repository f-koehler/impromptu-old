#ifndef IMPROMPTU_LIBGIT2_HPP
#define IMPROMPTU_LIBGIT2_HPP

#include <git2.h>

class Libgit2 {
  private:
    static bool initialized;

  public:
    Libgit2() {
        if (initialized) {
            git_libgit2_init();
            initialized = true;
        }
    }

    virtual ~Libgit2() {
        if (initialized)
            git_libgit2_shutdown();
    }
};
bool Libgit2::initialized = false;

class GitRepository {
  public:
    using GitRepositoryUniquePtr =
        std::unique_ptr<git_repository, decltype(&git_repository_free)>;
    using GitReferenceUniquePtr =
        std::unique_ptr<git_reference, decltype(&git_reference_free)>;

  private:
    const std::string path;
    GitRepositoryUniquePtr repo;

    auto open_repo(const std::string &path) {
        git_repository *raw = nullptr;
        git_repository_open(&raw, path.c_str());
        return GitRepositoryUniquePtr{std::move(raw), git_repository_free};
    }

    auto get_head() {
        git_reference *raw = nullptr;
        git_repository_head(&raw, repo.get());
        return GitReferenceUniquePtr{std::move(raw), git_reference_free};
    }

  public:
    GitRepository(const std::string &path)
        : path(path), repo(open_repo(path)) {}
};

#endif
