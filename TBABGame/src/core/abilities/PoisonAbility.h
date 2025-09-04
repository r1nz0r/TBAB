#pragma once
#include "core/interfaces/IAttackModifier.h"

namespace TBAB
{
    /**
     * @class PoisonAbility
     * @brief An ability that applies escalating bonus damage over time.
     * * The damage bonus starts on the second turn and increases with each subsequent turn.
     */
    class PoisonAbility final : public IAttackModifier
    {
    public:
        static constexpr int TURN_NUMBER_TO_APPLY = 2;

        /**
         * @brief Adds a damage bonus that scales with the turn count.
         * @param damage The current damage value to be modified.
         * @param attacker The creature that is attacking.
         * @param defender The creature that is being attacked.
         * @param turnCount The current turn number in the battle.
         */
        void ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
}
