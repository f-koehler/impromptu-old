#include <iostream>

#include <impromptu.hpp>

using namespace impromptu;

auto generate_line(int length, const std::string symbol = u8"─") {
    std::ostringstream ss;
    for (int i = 0; i < length; ++i) {
        ss << symbol;
    }
    return ss.str();
}

int main(int argc, const char *argv[]) {
    ExternalInfo info(argc, argv);

    const auto shell = get_shell();
    const TerminalSize term_size;

    std::cout << FGYellow << shell << ' '
              << generate_line(term_size.width - 10 - shell.length()) << ' '
              << get_time() << '\n';

    if (info.exit_code == 0) {
        std::cout << FGGreen << u8"✓ ";
    } else {
        std::cout << FGRed << u8"✘ ";
    }

    if (info.number_of_jobs > 0) {
        std::cout << FGBlue << u8"⚙ ";
    }
    std::cout << Bold << FGGreen << get_username() << '@' << get_hostname()
              << Reset << ' ' << FGRed << shorten_path(get_cwd()).native()
              << Bold << FGGreen << " $ " << Reset;
}
