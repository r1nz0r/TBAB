#pragma once
#include "core/interfaces/IAttackModifier.h"

namespace TBAB
{
    class FireBreathAbility final : public IAttackModifier
    {
    public:
        static constexpr int TURN_NUMBER_TO_APPLY = 3;
        static constexpr int DAMAGE_AMPLIFIER = 3;
        
        void ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
}
