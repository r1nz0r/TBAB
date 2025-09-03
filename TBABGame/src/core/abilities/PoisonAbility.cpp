#include "PoisonAbility.h"
#include "core/entities/Creature.h"

namespace TBAB
{
    void PoisonAbility::ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const
    {
        if (turnCount > 1)
        {
            damage += (turnCount - 1);
        }
    }
} // namespace TBAB
