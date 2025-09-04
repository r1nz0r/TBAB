#include "core/entities/Player.h"
#include <utility>

namespace TBAB
{
    Player::Player(std::string name, const int health, Attributes attributes, std::unique_ptr<Weapon> startingWeapon)
        : Creature(std::move(name), health, attributes, std::move(startingWeapon))
    {
    }
    
    void Player::LevelUp()
    {
        ++m_level;
    }
    
    void Player::RestoreHealth()
    {
        m_currentHealth = m_maxHealth;
    }

    void Player::EquipWeapon(std::unique_ptr<Weapon> newWeapon)
    {
        m_damageSource = std::move(newWeapon);
    }

    int Player::GetLevel() const
    {
        return m_level;
    }
} // namespace TBAB
