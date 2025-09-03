#include "FireBreathAbility.h"
#include "core/entities/Creature.h"

namespace TBAB
{
    void FireBreathAbility::ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const
    {
        if (turnCount % 3 == 0)
        {
            damage += 3;
        }
    }
} // namespace TBAB
