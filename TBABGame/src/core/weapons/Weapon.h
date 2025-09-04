#pragma once

#include "core/interfaces/IDamageSource.h"
#include <string>

namespace TBAB
{
    /**
     * @class Weapon
     * @brief A concrete implementation of IDamageSource representing an equippable weapon.
     */
    class Weapon final : public IDamageSource
    {
    public:
        Weapon(std::string name, int baseDamage, DamageType damageType);

        [[nodiscard]] int GetBaseDamage() const override;
        [[nodiscard]] DamageType GetDamageType() const override;
        [[nodiscard]] const std::string& GetName() const override;

    private:
        std::string m_name;
        int m_baseDamage;
        DamageType m_damageType;
    };
} // namespace TBAB
