#pragma once
#include "core/interfaces/IAttackModifier.h"

namespace TBAB
{
    class PoisonAbility final : public IAttackModifier
    {
    public:
        void ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
}
