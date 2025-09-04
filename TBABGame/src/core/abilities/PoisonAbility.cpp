#include "PoisonAbility.h"
#include "core/entities/Creature.h"

namespace TBAB
{    
    void PoisonAbility::ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const
    {
        if (turnCount >= TURN_NUMBER_TO_APPLY)
        {
            damage += (turnCount - 1);
        }
    }
} // namespace TBAB
