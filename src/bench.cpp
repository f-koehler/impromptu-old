#include <benchmark/benchmark.h>

#include <future>

#include <impromptu/external_info.hpp>
#include <impromptu/git.hpp>
#include <impromptu/host.hpp>
#include <impromptu/shell.hpp>
#include <impromptu/terminal.hpp>
#include <impromptu/time.hpp>
#include <impromptu/user.hpp>
#include <impromptu/vcs.hpp>

using namespace impromptu;

static void BM_ExternalInfo(benchmark::State &state) {
    int argc = 5;
    const char *argv[] = {"exe", "-r", "1", "-j",
                          "[1]    suspended  A\n[2]    suspended  B\n[3]  - "
                          "suspended  C\n[4]  + suspended  D\n"};

    for (auto _ : state) {
        benchmark::DoNotOptimize(ExternalInfo(argc, argv));
    }
}
BENCHMARK(BM_ExternalInfo);

static void BM_GitRepository(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(GitRepository("/home/fkoehler/.emacs.d/"));
    }
}
BENCHMARK(BM_GitRepository);

static void BM_GitRepository_get_action(benchmark::State &state) {
    for (auto _ : state) {
        auto repo = GitRepository("/home/fkoehler/.emacs.d/");
        repo.get_action();
    }
}
BENCHMARK(BM_GitRepository_get_action);

static void BM_GitRepository_get_hash(benchmark::State &state) {
    for (auto _ : state) {
        auto repo = GitRepository("/home/fkoehler/.emacs.d/");
        repo.get_hash();
    }
}
BENCHMARK(BM_GitRepository_get_hash);

static void BM_get_cwd(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(get_cwd());
    }
}
BENCHMARK(BM_get_cwd);

static void BM_get_shell(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(get_shell());
    }
}
BENCHMARK(BM_get_shell);

static void BM_get_home_directory(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(get_home_directory());
    }
}
BENCHMARK(BM_get_home_directory);

static void BM_get_hostname(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(get_hostname());
    }
}
BENCHMARK(BM_get_hostname);

static void BM_TerminalSize(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(TerminalSize());
    }
}
BENCHMARK(BM_TerminalSize);

static void BM_get_time(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(get_time());
    }
}
BENCHMARK(BM_get_time);

static void BM_get_username(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(get_username());
    }
}
BENCHMARK(BM_get_username);

static void BM_detect_vcs(benchmark::State &state) {
    std::filesystem::path path(".");
    for (auto _ : state) {
        benchmark::DoNotOptimize(detect_vcs(path));
    }
}
BENCHMARK(BM_detect_vcs);

BENCHMARK_MAIN();
