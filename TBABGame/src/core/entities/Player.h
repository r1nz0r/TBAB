#pragma once

#include "core/entities/Creature.h"
#include "core/weapons/Weapon.h"
#include <memory>

namespace TBAB
{
    class Player final : public Creature
    {
    public:
        Player(std::string name, const int health, Attributes attributes, std::unique_ptr<Weapon> startingWeapon);

        void LevelUp();
        void RestoreHealth();
        void EquipWeapon(std::unique_ptr<Weapon> newWeapon);
        [[nodiscard]] int GetLevel() const;
        
    private:
        int m_level = 1;
    };
} // namespace TBAB
