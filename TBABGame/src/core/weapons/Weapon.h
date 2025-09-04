#pragma once

#include "core/interfaces/IDamageSource.h"
#include <string>

namespace TBAB
{
    /**
     * @class Weapon
     * @brief A concrete implementation of IDamageSource representing an equippable weapon.
     *
     * This class holds the properties of a weapon, such as its name, base damage, and
     * damage type. It fulfills the `IDamageSource` interface, allowing it to be
     * used as a source of damage in combat.
     */
    class Weapon final : public IDamageSource
    {
    public:
        
        /**
         * @brief Constructs a new Weapon object.
         * @param name The name of the weapon.
         * @param baseDamage The base damage value of the weapon.
         * @param damageType The type of damage the weapon deals.
         */
        Weapon(std::string name, int baseDamage, DamageType damageType);

        /**
         * @brief Gets the base damage of the weapon.
         * @return The base damage as an integer.
         */
        [[nodiscard]] int GetBaseDamage() const override;
        
        /**
         * @brief Gets the damage type of the weapon.
         * @return The `DamageType` enum value.
         */
        [[nodiscard]] DamageType GetDamageType() const override;
        
        /**
         * @brief Gets the name of the weapon.
         * @return A constant reference to the weapon's name string.
         */
        [[nodiscard]] const std::string& GetName() const override;

    private:
        std::string m_name;
        int m_baseDamage;
        DamageType m_damageType;
    };
} // namespace TBAB
