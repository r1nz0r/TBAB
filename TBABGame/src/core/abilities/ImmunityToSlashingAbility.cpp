#include "ImmunityToSlashingAbility.h"
#include "core/entities/Creature.h"

namespace TBAB
{
    void ImmunityToSlashingAbility::ModifyDefense(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const
    {
        if (attacker.GetDamageSource() && attacker.GetDamageSource()->GetDamageType() == DamageType::Slashing)
        {
            damage -= attacker.GetDamageSource()->GetBaseDamage();
        }
    }
}
