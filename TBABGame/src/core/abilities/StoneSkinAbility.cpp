#include "StoneSkinAbility.h"
#include "core/entities/Creature.h"
#include <algorithm>

namespace TBAB
{
    void StoneSkinAbility::ModifyDefense(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const
    {
        damage = std::max(0, damage - defender.GetAttributes().endurance);
    }
}
