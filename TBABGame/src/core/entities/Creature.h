#pragma once

#include "core/Types.h"
#include "core/interfaces/IDamageSource.h"
#include "core/interfaces/IAttackModifier.h"
#include "core/interfaces/IDefenseModifier.h"

#include <string>
#include <memory>
#include <vector>

namespace TBAB
{
    /**
     * @class Creature
     * @brief An abstract base class for any participant in a battle (Player or Monster).
     */
    class Creature
    {
    public:
        Creature(std::string name, Attributes attributes, std::unique_ptr<IDamageSource> damageSource);
        virtual ~Creature() = default;

        bool IsAlive() const;

        [[nodiscard]] virtual const std::string& GetName() const;
        [[nodiscard]] virtual const Attributes& GetAttributes() const;
        virtual void TakeDamage(int amount) = 0;

        // TODO:
        // Add more methods like AddAttackModifier, CalculateDamage, etc.

    protected:
        std::string m_name;
        Attributes m_attributes;
        int m_currentHealth;
        int m_maxHealth;

        std::unique_ptr<IDamageSource> m_damageSource;

        std::vector<std::unique_ptr<IAttackModifier>> m_attackModifiers;
        std::vector<std::unique_ptr<IDefenseModifier>> m_defenseModifiers;
    };
} // namespace TBAB
