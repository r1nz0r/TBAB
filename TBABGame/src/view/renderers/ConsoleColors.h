#pragma once
#include <string_view>

namespace TBAB::Colors
{
    inline constexpr std::string_view RESET = "\033[0m";
    inline constexpr std::string_view BLACK = "\033[30m";
    inline constexpr std::string_view RED = "\033[31m";
    inline constexpr std::string_view GREEN = "\033[32m";
    inline constexpr std::string_view YELLOW = "\033[33m";
    inline constexpr std::string_view BLUE = "\033[34m";
    inline constexpr std::string_view MAGENTA = "\033[35m";
    inline constexpr std::string_view CYAN = "\033[36m";
    inline constexpr std::string_view WHITE = "\033[37m";

    inline constexpr std::string_view BOLD_RED = "\033[1;31m";
    inline constexpr std::string_view BOLD_GREEN = "\033[1;32m";
    inline constexpr std::string_view BOLD_YELLOW = "\033[1;33m";
    inline constexpr std::string_view BOLD_BLUE = "\033[1;34m";
    inline constexpr std::string_view BOLD_MAGENTA = "\033[1;35m";
    inline constexpr std::string_view BOLD_CYAN = "\033[1;36m";
    inline constexpr std::string_view BOLD_WHITE = "\033[1;37m";

    inline constexpr std::string_view GREY = "\033[90m";
} // namespace TBAB::Colors
