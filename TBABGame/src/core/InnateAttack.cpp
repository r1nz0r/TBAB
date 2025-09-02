#include "core/InnateAttack.h"

namespace TBAB
{
    InnateAttack::InnateAttack(int baseDamage, DamageType damageType)
        : m_baseDamage(baseDamage), m_damageType(damageType)
    {
    }

    int InnateAttack::GetBaseDamage() const
    {
        return m_baseDamage;
    }

    DamageType InnateAttack::GetDamageType() const
    {
        return m_damageType;
    }
}