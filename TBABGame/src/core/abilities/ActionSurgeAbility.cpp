#include "ActionSurgeAbility.h"
#include "core/entities/Creature.h"

namespace TBAB
{
    void ActionSurgeAbility::ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const
    {
        if (turnCount == TURN_NUMBER_TO_APPLY)
        {
            if (attacker.GetDamageSource())
            {
                damage += attacker.GetDamageSource()->GetBaseDamage();
            }
        }
    }
} // namespace TBAB
