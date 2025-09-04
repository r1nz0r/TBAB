#pragma once

#include "core/interfaces/IAttackModifier.h"

namespace TBAB
{
    /**
     * @class RageAbility
     * @brief Implements the Barbarian's Rage: +2 damage for the first 3 turns, -1 damage afterwards.
     */
    class RageAbility final : public IAttackModifier
    {
    public:
        static constexpr int DAMAGE_BONUS_DURATION_IN_TURNS = 3;
        static constexpr int DAMAGE_BONUS = 2;
        static constexpr int DAMAGE_PENALTY = -1;

        /**
        * @brief Modifies the damage value based on the number of turns.
        * @param damage The current damage value that will be modified.
        * @param attacker The creature that is attacking.
        * @param defender The creature that is defending.
        * @param turnCount The current turn number in combat.
        */
        void ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
} // namespace TBAB