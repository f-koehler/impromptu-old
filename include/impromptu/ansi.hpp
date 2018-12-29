#ifndef IMPROMPTU_ANSI_HPP
#define IMPROMPTU_ANSI_HPP

namespace impromptu {
struct AnsiCode {
    const int code;
};

std::ostream &operator<<(std::ostream &strm, const AnsiCode &code) {
    strm << "\033[" << code.code << "m";
    return strm;
}

constexpr AnsiCode Reset{0}, Bold{1}, Faint{2}, Italic{3}, Underline{4},
    SlowBlink{5}, RapidBlink{6}, ReverseVideo{7}, Conceal{8}, CrossedOut{9},
    Fraktur{20}, BoldOff{21}, DoublyUnderline{21}, NormalIntensity{22},
    NonItalic{23}, NonUnderline{24}, BlinkOff{25}, InverseOff{27}, Reveal{28},
    NotCrossedOut{29}, Framed{51}, Encircled{52}, Overlined{53}, NotFramed{54},
    NotEncircled{54}, NotOverlined{55};

constexpr AnsiCode FGBlack{30}, FGRed{31}, FGGreen{32}, FGYellow{33},
    FGBlue{34}, FGMagenta{35}, FGCyan{36}, FGWhite{37}, FGDefault{39};

constexpr AnsiCode BGBlack{40}, BGRed{41}, BGGreen{42}, BGYellow{43},
    BGBlue{44}, BGMagenta{45}, BGCyan{46}, BGWhite{47}, BGDefault{49};

constexpr AnsiCode FGBlackBright{90}, FGRedBright{91}, FGGreenBright{92},
    FGYellowBright{93}, FGBlueBright{94}, FGMagentaBright{95}, FGCyanBright{96},
    FGWhiteBright{97};

constexpr AnsiCode BGBlackBright{100}, BGRedBright{101}, BGGreenBright{102},
    BGYellowBright{103}, BGBlueBright{104}, BGMagentaBright{105},
    BGCyanBright{106}, BGWhiteBright{107};

} // namespace impromptu

#endif
