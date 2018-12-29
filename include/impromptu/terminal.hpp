#ifndef IMPROMPTU_TERMINAL_HPP
#define IMPROMPTU_TERMINAL_HPP

#include <cstdio>

#include <sys/ioctl.h>

namespace impromptu {
struct TerminalSize {
    int width;
    int height;

    TerminalSize() {
        struct winsize size;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
            width = 80;
            height = 10;
        } else {
            width = size.ws_col;
            height = size.ws_row;
        }
    }
};
} // namespace impromptu

#endif
