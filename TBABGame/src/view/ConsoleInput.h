#pragma once

#include "core/common/Choices.h"
#include <string>

namespace TBAB
{
    /**
     * @class ConsoleInput
     * @brief Class designed to take input from user via console
     */
    class ConsoleInput
    {
    public:
        std::string GetPlayerName();
        PlayerClassChoice GetPlayerClass();
    };
} // namespace TBAB
