#pragma once
#include <string>
#include "core/common/Types.h" 

namespace TBAB::Events
{
    struct Event
    {
        virtual ~Event() = default;
    };

    struct AbilityUsed : public Event
    {
        std::string userName;
        std::string abilityName;
        std::string message;

        AbilityUsed(std::string userName, std::string abilityName, std::string message)
           : userName(std::move(userName)), abilityName(std::move(abilityName)), message(std::move(message)) {}
    };

    struct DamageApplied : public Event
    {
        std::string targetName;
        int damageAmount;
        int currentHp;
        int maxHp;

        DamageApplied(std::string targetName, int damageAmount, int currentHp, int maxHp)
           : targetName(std::move(targetName)), damageAmount(damageAmount), currentHp(currentHp), maxHp(maxHp) {}
    };

    struct AttackMissed : public Event
    {
        std::string attackerName;
        std::string defenderName;

        AttackMissed(std::string attackerName, std::string defenderName)
           : attackerName(std::move(attackerName)), defenderName(std::move(defenderName)) {}
    };
}

