#include "Weapon.h"
#include <utility>

namespace TBAB
{
    Weapon::Weapon(std::string name, int baseDamage, DamageType damageType)
        : m_name(std::move(name)), m_baseDamage(baseDamage), m_damageType(damageType)

    {
    }

    int Weapon::GetBaseDamage() const
    {
        return m_baseDamage;
    }

    DamageType Weapon::GetDamageType() const
    {
        return m_damageType;
    }

    const std::string& Weapon::GetName() const
    {
        return m_name;
    }

} // namespace TBAB
