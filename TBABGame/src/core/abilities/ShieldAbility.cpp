#include "ShieldAbility.h"
#include "core/entities/Creature.h"
#include <algorithm>

namespace TBAB
{
    void ShieldAbility::ModifyDefense(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const
    {
        if (defender.GetAttributes().strength > attacker.GetAttributes().strength)
        {
            damage = std::max(0, damage - DAMAGE_REDUCTION);
        }
    }
}
