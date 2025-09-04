#pragma once

#include "core/entities/Creature.h"
#include "core/weapons/Weapon.h"
#include <memory>

namespace TBAB
{
    class Monster final : public Creature
    {
    public:
        Monster(std::string name, Attributes attributes, const int health, const int innateDamage, DamageType innateDamageType,
            std::unique_ptr<Weapon> droppedWeapon);

        [[nodiscard]] std::string GetDroppedWeaponName() const;
        [[nodiscard]] std::unique_ptr<Weapon> TakeDroppedWeapon();

    private:
        std::unique_ptr<Weapon> m_droppedWeapon;
    };
} // namespace TBAB