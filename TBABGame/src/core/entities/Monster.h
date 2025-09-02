#pragma once

#include "core/entities/Creature.h"
#include "core/Weapon.h"
#include <memory>

namespace TBAB
{
    class Monster final : public Creature
    {
    public:
        Monster(std::string name, Attributes attributes, const int health, const int innateDamage, DamageType innateDamageType,
            std::unique_ptr<Weapon> droppedWeapon);

        const Weapon* GetDroppedWeapon() const;
        virtual void TakeDamage(int amount) override;

    private:
        std::unique_ptr<Weapon> m_droppedWeapon;
    };
} // namespace TBAB