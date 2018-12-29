#ifndef IMPROMPTU_HOST_HPP
#define IMPROMPTU_HOST_HPP

#include <unistd.h>

namespace impromptu {
auto get_hostname() {
    char name[256];
    if (gethostname(name, 256) != 0) {
        name[0] = '\0';
    }
    return std::string(name);
}
} // namespace impromptu

#endif
