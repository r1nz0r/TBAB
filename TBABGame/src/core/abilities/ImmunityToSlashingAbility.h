#pragma once
#include "core/interfaces/IDefenseModifier.h"

namespace TBAB
{
    class ImmunityToSlashingAbility final : public IDefenseModifier
    {
    public:
        void ModifyDefense(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
}
