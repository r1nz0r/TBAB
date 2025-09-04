#pragma once
#include "core/interfaces/IDefenseModifier.h"

namespace TBAB
{
    class ShieldAbility final : public IDefenseModifier
    {
    public:
        static constexpr int DAMAGE_REDUCTION = 3;
        
        void ModifyDefense(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
}
