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
        
        void ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
} // namespace TBAB