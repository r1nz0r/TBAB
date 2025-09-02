#include "Creature.h"
#include <utility>

namespace TBAB
{
    Creature::Creature(std::string name, Attributes attributes, std::unique_ptr<IDamageSource> damageSource)
        : m_name(std::move(name)), m_attributes(attributes), m_currentHealth(0), m_maxHealth(0), m_damageSource(std::move(damageSource))
    {
    }

    bool Creature::IsAlive() const
    {
        return m_currentHealth > 0;
    }
} // namespace TBAB
