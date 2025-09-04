#include "core/entities/Monster.h"
#include "core/weapons/Weapon.h"
#include <utility>

namespace TBAB
{

    Monster::Monster(std::string name, Attributes attributes, const int health, const int innateDamage, DamageType innateDamageType,
        std::unique_ptr<Weapon> droppedWeapon)
        : Creature(std::move(name), health, attributes, std::make_unique<Weapon>("Innate Attack", innateDamage, innateDamageType)),
          m_droppedWeapon(std::move(droppedWeapon))
    {
    }

    std::string Monster::GetDroppedWeaponName() const
    {
        if (m_droppedWeapon)
        {
            return m_droppedWeapon->GetName();
        }
        return "None";
    }

    std::unique_ptr<Weapon> Monster::TakeDroppedWeapon()
    {
        return std::move(m_droppedWeapon);
    }
} // namespace TBAB