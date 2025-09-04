#include "core/abilities/RageAbility.h"
#include "core/entities/Creature.h"

namespace TBAB
{
    void RageAbility::ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const
    {
        damage += (turnCount <= DAMAGE_BONUS_DURATION_IN_TURNS) ? DAMAGE_BONUS : DAMAGE_PENALTY;
    }
} // namespace TBAB
