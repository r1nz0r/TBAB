#pragma once
#include "core/interfaces/IAttackModifier.h"

namespace TBAB
{
    /**
     * @class ActionSurgeAbility
     * @brief An ability that provides a damage bonus on the first turn of combat.
     * * This ability modifies the attacker's damage output to be equal to
     * their weapon's base damage on the first turn.
     */    
    class ActionSurgeAbility final : public IAttackModifier
    {
    public:
        static constexpr int TURN_NUMBER_TO_APPLY = 1;

        /**
         * @brief Modifies the attack damage on the first turn.
         * @param damage The current damage value to be modified.
         * @param attacker The creature that is attacking.
         * @param defender The creature that is being attacked.
         * @param turnCount The current turn number in the battle.
         */
        void ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
}
