#include "FireBreathAbility.h"
#include "core/entities/Creature.h"

namespace TBAB
{
    void FireBreathAbility::ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const
    {
        if (turnCount % TURN_NUMBER_TO_APPLY == 0)
        {
            damage += DAMAGE_AMPLIFIER;
        }
    }
} // namespace TBAB
