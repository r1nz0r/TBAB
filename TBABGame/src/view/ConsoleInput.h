#pragma once

#include "core/common/Choices.h"
#include <string>

namespace TBAB
{
    class IDamageSource;
    /**
     * @class ConsoleInput
     * @brief Class designed to take input from user via console
     */
    class ConsoleInput
    {
    public:
        std::string GetPlayerName();
        PlayerClassChoice GetPlayerClass();
        PostBattleChoice GetPostBattleChoice(const IDamageSource* currentWeapon, const IDamageSource& droppedWeapon);
    };
} // namespace TBAB
