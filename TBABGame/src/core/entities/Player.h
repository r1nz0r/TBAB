#pragma once

#include "core/entities/Creature.h"
#include "core/weapons/Weapon.h"

#include <map>
#include <memory>

namespace TBAB
{
    class Player final : public Creature
    {
    public:
        Player(std::string name, const int health, Attributes attributes, std::unique_ptr<Weapon> startingWeapon);

        void RestoreHealth();
        void EquipWeapon(std::unique_ptr<Weapon> newWeapon);
        void AddClassLevel(const std::string& classId);
        
        [[nodiscard]] int GetTotalLevel() const;
        [[nodiscard]] int GetLevelInClass(const std::string& classId) const;
        [[nodiscard]] const std::map<std::string, int>& GetClassLevels() const;
        
    private:
        std::map<std::string, int> m_classLevels;
    };
} // namespace TBAB
