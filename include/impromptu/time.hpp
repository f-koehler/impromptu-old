#ifndef IMPROMPTU_TIME_HPP
#define IMPROMPTU_TIME_HPP

#include <ctime>
#include <iomanip>
#include <sstream>

namespace impromptu {

auto get_time(const std::string format = "%H:%M:%S") {
    std::time_t t = std::time(nullptr);
    std::ostringstream ss;
    ss << std::put_time(std::localtime(&t), format.c_str());
    return ss.str();
}

} // namespace impromptu

#endif
