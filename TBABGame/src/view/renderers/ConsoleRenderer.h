#pragma once

#include "core/events/Event.h"

namespace TBAB
{
    class DataManager;
    class Creature;
    
    /**
     * @class ConsoleRenderer
     * @brief A concrete class that listens for battle events and outputs them to the console.
     * This class handles the visual representation of the game state in the console.
     */
    class ConsoleRenderer final
    {
    public:

        /**
         * @brief Constructs a new ConsoleRenderer.
         * @param dataManager A constant reference to the DataManager for accessing game data.
         */
        ConsoleRenderer(const DataManager& dataManager);

        /**
         * @brief Registers this renderer's methods as event handlers with the EventBus.
         */
        void RegisterEventHandlers();

    private:
        /**
         * @brief Handles the BattleStarted event.
         * @param event The BattleStarted event object.
         */
        void HandleBattleStart(const Events::BattleStarted& event);
        
        /**
         * @brief Handles the TurnStarted event.
         * @param event The TurnStarted event object.
         */
        void HandleTurnStarted(const Events::TurnStarted& event);
        
        /**
         * @brief Handles the DamageApplied event.
         * @param event The DamageApplied event object.
         */
        void HandleDamageApplied(const Events::DamageApplied& event);
        
        /**
         * @brief Handles the AttackMissed event.
         * @param event The AttackMissed event object.
         */
        void HandleAttackMissed(const Events::AttackMissed& event);
        
        /**
         * @brief Handles the BattleEnded event.
         * @param event The BattleEnded event object.
         */
        void HandleBattleEnded(const Events::BattleEnded& event);
        
        /**
         * @brief Handles the GameMessage event.
         * @param event The GameMessage event object.
         */
        void HandleGameMessage(const Events::GameMessage& event);
        
        /**
         * @brief Handles the ErrorMessage event.
         * @param event The ErrorMessage event object.
         */
        void HandleErrorMessage(const Events::ErrorMessage& event);
        
        /**
         * @brief Handles the NewGameStarted event.
         * @param event The NewGameStarted event object.
         */
        void HandleNewGameStarted(const Events::NewGameStarted& event);
        
        /**
         * @brief Handles the AbilityTriggered event.
         * @param event The AbilityTriggered event object.
         */
        void HandleAbilityTriggered(const Events::AbilityTriggered& event);
        
        /**
         * @brief Handles the GameWon event.
         * @param event The GameWon event object.
         */
        void HandleGameWon(const Events::GameWon& event);
        
        /**
         * @brief Handles the GameLost event.
         * @param event The GameLost event object.
         */
        void HandleGameLost(const Events::GameLost& event);

        /**
         * @brief Prints the detailed information of a creature to the console.
         * @param creature The creature whose information will be printed.
         */
        void PrintCreatureInfo(const Creature& creature) const;
        
        /**
         * @brief Prints a health bar for a creature.
         * @param current The current health of the creature.
         * @param max The maximum health of the creature.
         */
        void PrintHealthBar(int current, int max) const;
        
        /**
         * @brief Prints a compact health bar for a creature.
         * @param name The name of the creature.
         * @param current The current health of the creature.
         * @param max The maximum health of the creature.
         */
        void PrintCompactHealthBar(const std::string& name, int current, int max) const;
        
        /**
         * @brief Converts a DamageType enum value to its string representation.
         * @param type The DamageType enum value.
         * @return A string representing the damage type.
         */
        std::string DamageTypeToString(DamageType type) const;
        
        /**
         * @brief Clears the console screen.
         */
        void ClearScreen() const;

        const DataManager& m_dataManager;
    };
} // namespace TBAB
