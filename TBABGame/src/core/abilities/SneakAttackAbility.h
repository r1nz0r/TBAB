#pragma once
#include "core/interfaces/IAttackModifier.h"

namespace TBAB
{
    class SneakAttackAbility final : public IAttackModifier
    {
    public:
        static constexpr int DAMAGE_AMPLIFIER = 1;
        
        void ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
}
