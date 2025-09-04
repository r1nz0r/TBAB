#pragma once

#include "core/data/Choices.h"
#include <string>

namespace TBAB
{
    class IDamageSource;
    /**
     * @class ConsoleInput
     * @brief Class designed to take input from user via console.
     *
     * This class provides methods for handling various types of user input, such as
     * selecting a character class, making choices after a battle, or providing a name.
     */
    class ConsoleInput
    {
    public:
        /**
         * @brief Prompts the user to enter a name for their hero.
         * @return The name entered by the user.
         */
        std::string GetPlayerName();
        
        /**
         * @brief Prompts the user to choose a starting class.
         * @return The selected PlayerClassChoice.
         */
        PlayerClassChoice GetPlayerClass();
        
        /**
         * @brief Prompts the user to choose a class to level up.
         * @return The selected PlayerClassChoice.
         */
        PlayerClassChoice GetLevelUpClassChoice();
        
        /**
         * @brief Prompts the user to choose whether to take a dropped weapon.
         * @param currentWeapon A pointer to the player's current weapon.
         * @param droppedWeapon A constant reference to the dropped weapon.
         * @return The user's choice (TakeWeapon or LeaveWeapon).
         */
        PostBattleChoice GetPostBattleChoice(const IDamageSource* currentWeapon, const IDamageSource& droppedWeapon);
        
        /**
         * @brief Asks the user if they want to play the game again.
         * @return True if the user wants to play again, false otherwise.
         */
        bool AskToPlayAgain();
        
    private:
        /**
         * @brief A helper method for handling class choice input with validation.
         * @param prompt The message to display to the user.
         * @return The selected PlayerClassChoice.
         */
        PlayerClassChoice GetClassChoiceInternal(const std::string& prompt);
        
        /**
         * @brief A helper method for handling yes/no input with validation.
         * @param prompt The yes/no question to display to the user.
         * @return True for 'y', false for 'n'.
         */
        bool GetYesNoChoice(const std::string& prompt);
    };
} // namespace TBAB
