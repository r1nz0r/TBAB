#include "SneakAttackAbility.h"
#include "core/entities/Creature.h"

namespace TBAB
{
    static constexpr int DAMAGE_AMPLIFIER = 3;
    
    void SneakAttackAbility::ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const
    {
        if (attacker.GetAttributes().dexterity > defender.GetAttributes().dexterity)
        {
            damage += DAMAGE_AMPLIFIER;
        }
    }
}
