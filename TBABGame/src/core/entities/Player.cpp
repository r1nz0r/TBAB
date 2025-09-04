#include "core/entities/Player.h"
#include <utility>

namespace TBAB
{
    Player::Player(std::string name, const int health, Attributes attributes, std::unique_ptr<Weapon> startingWeapon)
        : Creature(std::move(name), health, attributes, std::move(startingWeapon))
    {
    }

    void Player::RestoreHealth()
    {
        m_currentHealth = m_maxHealth;
    }

    void Player::EquipWeapon(std::unique_ptr<Weapon> newWeapon)
    {
        m_damageSource = std::move(newWeapon);
    }

    void Player::AddClassLevel(const std::string& classId)
    {
        m_classLevels[classId]++;
    }

    int Player::GetTotalLevel() const
    {
        int totalLevel = 0;
        for (const auto& pair : m_classLevels)
        {
            totalLevel += pair.second;
        }
        return totalLevel;
    }

    int Player::GetLevelInClass(const std::string& classId) const
    {
        auto it = m_classLevels.find(classId);
        if (it != m_classLevels.end())
        {
            return it->second;
        }
        return 0;
    }

    const std::map<std::string, int>& Player::GetClassLevels() const
    {
        return m_classLevels;
    }
} // namespace TBAB
