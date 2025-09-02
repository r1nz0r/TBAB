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
        void ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
} // namespace TBAB