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
        PlayerClassChoice GetLevelUpClassChoice();
        PostBattleChoice GetPostBattleChoice(const IDamageSource* currentWeapon, const IDamageSource& droppedWeapon);
        bool AskToPlayAgain();
        
    private:
        PlayerClassChoice GetClassChoiceInternal(const std::string& prompt);
        bool GetYesNoChoice(const std::string& prompt);
    };
} // namespace TBAB
