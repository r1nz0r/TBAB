#pragma once
#include "core/entities/Creature.h"

#include <string>
#include <utility> // For std::move

namespace TBAB::Events
{
    struct Event
    {
        virtual ~Event() = default;
    };

    struct GameMessage : public Event
    {
        std::string message;
        GameMessage(std::string msg) : message(std::move(msg)) {}
    };

    struct ErrorMessage : public Event
    {
        std::string message;
        ErrorMessage(std::string msg) : message(std::move(msg)) {}
    };

    struct BattleStarted : public Event
    {
        const Creature* combatant1;
        const Creature* combatant2;

        BattleStarted(const Creature* c1, const Creature* c2) : combatant1(c1), combatant2(c2) {}
    };

    struct NewGameStarted : public Event
    {
    };

    struct TurnStarted : public Event
    {
        std::string attackerName;
        std::string defenderName;

        TurnStarted(std::string attackerName, std::string defenderName)
            : attackerName(std::move(attackerName)), defenderName(std::move(defenderName))
        {
        }
    };

    struct DamageApplied : public Event
    {
        std::string targetName;
        int damageAmount;
        int currentHp;
        int maxHp;

        DamageApplied(std::string targetName, int damageAmount, int currentHp, int maxHp)
            : targetName(std::move(targetName)), damageAmount(damageAmount), currentHp(currentHp), maxHp(maxHp)
        {
        }
    };

    struct AttackMissed : public Event
    {
        std::string attackerName;
        std::string defenderName;

        AttackMissed(std::string attackerName, std::string defenderName)
            : attackerName(std::move(attackerName)), defenderName(std::move(defenderName))
        {
        }
    };

    struct BattleEnded : public Event
    {
        std::string winnerName;

        explicit BattleEnded(std::string winnerName) : winnerName(std::move(winnerName)) {}
    };

    struct AbilityTriggered : public Event
    {
        std::string creatureName;
        std::string abilityId;

        AbilityTriggered(std::string creatureName, std::string abilityId)
            : creatureName(std::move(creatureName)), abilityId(std::move(abilityId))
        {
        }
    };

} // namespace TBAB::Events

