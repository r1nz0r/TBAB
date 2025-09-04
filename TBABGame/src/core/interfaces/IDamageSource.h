#pragma once

#include "core/data/Types.h"

#include <string>

namespace TBAB
{
    /**
     * @interface IDamageSource
     * @brief Represents an entity that can be a source of damage, like a weapon or a natural attack.
     */
    class IDamageSource
    {
    public:
        virtual ~IDamageSource() = default;

        [[nodiscard]] virtual int GetBaseDamage() const = 0;
        [[nodiscard]] virtual DamageType GetDamageType() const = 0;
        [[nodiscard]] virtual const std::string& GetName() const = 0;
    };
} // namespace TBAB
