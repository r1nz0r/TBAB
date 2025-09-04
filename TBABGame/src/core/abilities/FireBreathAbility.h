#pragma once
#include "core/interfaces/IAttackModifier.h"

namespace TBAB
{
    /**
     * @class FireBreathAbility
     * @brief An ability that deals bonus damage every third turn.
     * * This ability, typically used by a dragon, adds a fixed amount of damage
     * to the attack on specific turns.
     */    
    class FireBreathAbility final : public IAttackModifier
    {
    public:
        static constexpr int TURN_NUMBER_TO_APPLY = 3;
        static constexpr int DAMAGE_AMPLIFIER = 3;

        /**
         * @brief Adds bonus damage on every third turn.
         * @param damage The current damage value to be modified.
         * @param attacker The creature that is attacking.
         * @param defender The creature that is being attacked.
         * @param turnCount The current turn number in the battle.
         */
        void ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
}
