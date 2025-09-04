#pragma once
#include "core/interfaces/IDefenseModifier.h"

namespace TBAB
{
    /**
     * @class ImmunityToSlashingAbility
     * @brief An ability that negates damage from slashing attacks.
     * * This defense modifier is designed to absorb all base damage from an
     * attacker's weapon if its damage type is slashing.
     */    
    class ImmunityToSlashingAbility final : public IDefenseModifier
    {
    public:
        
        /**
         * @brief Reduces the incoming damage if the attacker's weapon is of slashing type.
         * @param damage The current damage value to be modified.
         * @param attacker The creature that is attacking.
         * @param defender The creature that is receiving the damage.
         * @param turnCount The current turn number in the battle.
         */
        void ModifyDefense(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
}
