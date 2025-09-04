#pragma once

#include "core/entities/Creature.h"
#include "core/weapons/Weapon.h"
#include <memory>

namespace TBAB
{
    /**
     * @class Monster
     * @brief A concrete class representing a monster in the game.
     *
     * Monsters are creatures that can be fought and defeated by the player.
     * They have an innate attack and may drop a weapon upon defeat.
     */
    class Monster final : public Creature
    {
    public:
        
        /**
         * @brief Constructs a Monster object.
         * @param name The name of the monster.
         * @param attributes The core attributes (Strength, Dexterity, Endurance) of the monster.
         * @param health The starting health of the monster.
         * @param innateDamage The base damage of the monster's natural attack.
         * @param innateDamageType The damage type of the monster's natural attack.
         * @param droppedWeapon A unique pointer to the weapon the monster will drop.
         */
        Monster(std::string name, Attributes attributes, const int health, const int innateDamage, DamageType innateDamageType,
            std::unique_ptr<Weapon> droppedWeapon);

        /**
         * @brief Gets the name of the weapon the monster will drop.
         * @return The name of the dropped weapon, or "None" if there is no weapon.
         */
        [[nodiscard]] std::string GetDroppedWeaponName() const;
        
        /**
         * @brief Takes ownership of the dropped weapon, removing it from the monster.
         * @return A unique pointer to the dropped weapon.
         */
        [[nodiscard]] std::unique_ptr<Weapon> TakeDroppedWeapon();

    private:
        std::unique_ptr<Weapon> m_droppedWeapon;
    };
} // namespace TBAB
