#pragma once

#include "core/interfaces/IDamageSource.h"
#include <string>

namespace TBAB
{
    /**
     * @class InnateAttack
     * @brief Represents a creature's natural attack (claws, bite, etc.).
     * This is a simple implementation of IDamageSource, similar to Weapon,
     * but it's not something that can be dropped or equipped.
     */
    class InnateAttack final : public IDamageSource
    {
    public:
        InnateAttack(int baseDamage, DamageType damageType);

        [[nodiscard]] int GetBaseDamage() const override;
        [[nodiscard]] DamageType GetDamageType() const override;
        [[nodiscard]] std::string GetName() const override;

    private:
        int m_baseDamage;
        DamageType m_damageType;
    };
} // namespace TBAB
