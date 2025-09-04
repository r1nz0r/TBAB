#pragma once

#include "core/events/Event.h"

namespace TBAB
{
    class DataManager;
    class Creature;
    /**
     * @class ConsoleRenderer
     * @brief A concrete class that listens for battle events and outputs them to the console.
     */
    class ConsoleRenderer final
    {
    public:
        ConsoleRenderer(const DataManager& dataManager);
        void RegisterEventHandlers();

    private:
        void HandleBattleStart(const Events::BattleStarted& event);
        void HandleTurnStarted(const Events::TurnStarted& event);
        void HandleDamageApplied(const Events::DamageApplied& event);
        void HandleAttackMissed(const Events::AttackMissed& event);
        void HandleBattleEnded(const Events::BattleEnded& event);
        void HandleGameMessage(const Events::GameMessage& event);
        void HandleErrorMessage(const Events::ErrorMessage& event);
        void HandleNewGameStarted(const Events::NewGameStarted& event);
        void HandleAbilityTriggered(const Events::AbilityTriggered& event);
        void HandleGameWon(const Events::GameWon& event);
        void HandleGameLost(const Events::GameLost& event);

        void PrintCreatureInfo(const Creature& creature) const;
        void PrintHealthBar(int current, int max) const;
        void PrintCompactHealthBar(const std::string& name, int current, int max) const;
        std::string DamageTypeToString(DamageType type) const;
        void ClearScreen() const;

        const DataManager& m_dataManager;
    };
} // namespace TBAB
