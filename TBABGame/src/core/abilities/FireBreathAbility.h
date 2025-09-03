#pragma once
#include "core/interfaces/IAttackModifier.h"

namespace TBAB
{
    class FireBreathAbility final : public IAttackModifier
    {
    public:
        void ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
}
