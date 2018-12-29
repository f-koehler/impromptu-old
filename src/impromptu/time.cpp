#include "impromptu/time.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>

namespace impromptu {
std::string get_time(const std::string &format) {
    std::time_t t = std::time(nullptr);
    std::ostringstream ss;
    ss << std::put_time(std::localtime(&t), format.c_str());
    return ss.str();
}
} // namespace impromptu
