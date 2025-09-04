#pragma once

#include "core/entities/Creature.h"
#include "core/weapons/Weapon.h"

#include <map>
#include <memory>

namespace TBAB
{
    /**
     * @class Player
     * @brief A concrete class representing the player character.
     *
     * The Player class inherits from Creature and adds specific player-related
     * functionality, such as class levels, health restoration, and weapon management.
     */
    class Player final : public Creature
    {
    public:
        
        /**
         * @brief Constructs a new Player object.
         * @param name The name of the player.
         * @param health The starting health of the player.
         * @param attributes The core attributes (Strength, Dexterity, Endurance) of the player.
         * @param startingWeapon A unique pointer to the player's starting weapon.
         */
        Player(std::string name, const int health, Attributes attributes, std::unique_ptr<Weapon> startingWeapon);

        /**
         * @brief Restores the player's health to its maximum value.
         */
        void RestoreHealth();
        
        /**
         * @brief Equips a new weapon, replacing the current one.
         * @param newWeapon A unique pointer to the new weapon.
         */
        void EquipWeapon(std::unique_ptr<Weapon> newWeapon);
        
        /**
         * @brief Adds a level to a specific character class.
         * @param classId The ID of the class to level up.
         */
        void AddClassLevel(const std::string& classId);
        
        /**
         * @brief Gets the total level of the player across all classes.
         * @return The sum of all class levels.
         */
        [[nodiscard]] int GetTotalLevel() const;
        
        /**
         * @brief Gets the level in a specific character class.
         * @param classId The ID of the class to check.
         * @return The level in the specified class, or 0 if the player has no levels in it.
         */
        [[nodiscard]] int GetLevelInClass(const std::string& classId) const;
        
        /**
         * @brief Gets a map of the player's class levels.
         * @return A constant reference to the map of class IDs to levels.
         */
        [[nodiscard]] const std::map<std::string, int>& GetClassLevels() const;
        
    private:
        std::map<std::string, int> m_classLevels;
    };
} // namespace TBAB
