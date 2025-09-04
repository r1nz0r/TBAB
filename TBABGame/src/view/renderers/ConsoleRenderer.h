#pragma once

#include "core/events/Event.h"

namespace TBAB
{
    /**
     * @class ConsoleRenderer
     * @brief A concrete class that listens for battle events and outputs them to the console.
     */
    class ConsoleRenderer final
    {
    public:
        void RegisterEventHandlers();

    private:
        void HandleBattleStart(const Events::BattleStarted& event);
        void HandleTurnStarted(const Events::TurnStarted& event);
        void HandleDamageApplied(const Events::DamageApplied& event);
        void HandleAttackMissed(const Events::AttackMissed& event);
        void HandleBattleEnded(const Events::BattleEnded& event);
        void HandleGameMessage(const Events::GameMessage& event);
        void HandleErrorMessage(const Events::ErrorMessage& event);
        
        void PrintCreatureInfo(const Creature& creature) const;
    };
}
