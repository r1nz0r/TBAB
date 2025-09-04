#pragma once
#include "core/interfaces/IAttackModifier.h"

namespace TBAB
{
    class ActionSurgeAbility final : public IAttackModifier
    {
    public:
        static constexpr int TURN_NUMBER_TO_APPLY = 1;

        void ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
}
