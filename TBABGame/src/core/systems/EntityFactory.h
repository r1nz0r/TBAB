#pragma once

#include "core/data/Choices.h"
#include <memory>
#include <string>
#include <string_view>

namespace TBAB
{
    class Weapon;
    class Player;
    class Monster;
    class DataManager;
}

namespace TBAB
{
    /**
    * @class EntityFactory
    * @brief Factory for creating game entities: player, monsters, and weapons.
    * * Uses DataManager to get data from JSON files and
    * creates corresponding objects with the correct characteristics.
    */
    class EntityFactory
    {
    public:
        
        /**
        * @brief Constructor of the entity factory.
        * @param dataManager Reference to the data manager used to get object templates.
        */
        EntityFactory(const DataManager& dataManager);
        
        /**
        * @brief Creates a new player object.
        * @param name Name of the player.
        * @param classChoice Choice of the player class.
        * @return std::unique_ptr<Player> Unique pointer to the created player object.
        */
        std::unique_ptr<Player> CreatePlayer(const std::string& name, PlayerClassChoice classChoice) const;
        
        /**
        * @brief Creates a new monster object given its ID.
        * @param monsterId The monster ID.
        * @return std::unique_ptr<Monster> A unique pointer to the created monster object.
        */
        std::unique_ptr<Monster> CreateMonster(std::string_view monsterId) const;

        /**
        * @brief Creates a random monster object from the available templates.
        * @return std::unique_ptr<Monster> A unique pointer to the created monster object.
        */
        std::unique_ptr<Monster> CreateRandomMonster() const;

        /**
        * @brief Creates a weapon object given its ID.
        * @param weaponId Weapon identifier.
        * @return std::unique_ptr<Weapon> Unique pointer to the created weapon object.
        */
        std::unique_ptr<Weapon> CreateWeapon(std::string_view weaponId) const;

    private:
        const DataManager& m_dataManager;
    };
} // namespace TBAB
