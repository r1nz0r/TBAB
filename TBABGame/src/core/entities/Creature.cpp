#include "Creature.h"
#include <utility>

namespace TBAB
{
    Creature::Creature(std::string name, const int health, Attributes attributes, std::unique_ptr<IDamageSource> damageSource)
        : m_name(std::move(name)), m_attributes(attributes), m_currentHealth(health), m_maxHealth(health),
          m_damageSource(std::move(damageSource))
    {
    }

    bool Creature::IsAlive() const
    {
        return m_currentHealth > 0;
    }

    const std::string& Creature::GetName() const
    {
        return m_name;
    }

    const Attributes& Creature::GetAttributes() const
    {
        return m_attributes;
    }
    
    int Creature::GetBaseDamage() const
    {
        return m_damageSource->GetBaseDamage();
    } 

    int Creature::GetCurrentHealth() const
    {
        return m_currentHealth;
    }

    int Creature::GetMaxHealth() const
    {
        return m_maxHealth;
    }

    void Creature::TakeDamage(const int amount)
    {
        if (amount > 0)
        {
            m_currentHealth = std::max(0, m_currentHealth - amount);
        }
    }
    int Creature::CalculateDamage() const
    {
        return m_damageSource->GetBaseDamage() + m_attributes.strength;
    }
} // namespace TBAB