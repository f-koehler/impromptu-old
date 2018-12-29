#include "impromptu/host.hpp"

namespace impromptu {
std::string get_hostname() {
    char name[256];
    if (gethostname(name, 256) != 0) {
        name[0] = '\0';
    }
    return std::string(name);
}
} // namespace impromptu
