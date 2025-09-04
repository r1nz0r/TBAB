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
    
     int Creature::GetCurrentHealth() const
    {
        return m_currentHealth;
    }

    int Creature::GetMaxHealth() const
    {
        return m_maxHealth;
    }
    
    const IDamageSource* Creature::GetDamageSource() const
    {
        return m_damageSource.get();
    }
    void Creature::TakeDamage(int& damage, const Creature& attacker, int turnNumber)
    {
        if (damage <= 0)
            return;

        for (const auto& modifier : m_defenseModifiers)
        {
            modifier->ModifyDefense(damage, attacker, *this, turnNumber);
        }

        if (damage > 0)
        {
            m_currentHealth = std::max(0, m_currentHealth - damage);
        }
    }
    void Creature::AddAttackModifier(std::unique_ptr<IAttackModifier> modifier)
    {
        m_attackModifiers.push_back(std::move(modifier));
    }
    
    void Creature::AddDefenseModifier(std::unique_ptr<IDefenseModifier> modifier)
    {
        m_defenseModifiers.push_back(std::move(modifier));
    }

    int Creature::CalculateDamage(const Creature& defender, const int turnNumber) const
    {
        int damage = m_damageSource->GetBaseDamage() + m_attributes.strength;
        
        for (const auto& modifier : m_attackModifiers)
        {
            modifier->ModifyAttack(damage, *this, defender, turnNumber);
        }

        return damage;
    }
} // namespace TBAB