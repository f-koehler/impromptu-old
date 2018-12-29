#ifndef IMPROMPTU_USER_HPP
#define IMPROMPTU_USER_HPP

#include <pwd.h>
#include <unistd.h>

namespace impromptu {

auto get_username() {
    auto uid = geteuid();
    errno = 0;
    auto pw = getpwuid(uid);
    if (pw == nullptr) {
        return std::string("");
    }
    return std::string(pw->pw_name);
}
} // namespace impromptu

#endif
