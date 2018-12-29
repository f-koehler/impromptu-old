#include "impromptu/terminal.hpp"

#include <cstdio>

#include <sys/ioctl.h>
#include <unistd.h>

namespace impromptu {
TerminalSize::TerminalSize() {
    struct winsize size;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
        width = 80;
        height = 10;
    } else {
        width = size.ws_col;
        height = size.ws_row;
    }
}
} // namespace impromptu
