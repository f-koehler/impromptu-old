#ifndef IMPROMPTU_EXTERNAL_INFO_HPP
#define IMPROMPTU_EXTERNAL_INFO_HPP

namespace impromptu {

struct ExternalInfo {
    ExternalInfo(int argc, const char *argv[]);

    int exit_code;
    int number_of_jobs;
};

} // namespace impromptu

#endif
