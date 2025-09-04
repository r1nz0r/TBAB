#pragma once

#include "core/data/AbilityData.h"
#include "core/data/CharacterClass.h"
#include "core/data/MonsterData.h"
#include "core/data/WeaponData.h"

#include <string>
#include <map>
#include <memory>
#include <filesystem>
#include <string_view>

namespace TBAB
{
    class Weapon;
    class Monster;

    /**
     * @class DataManager
     * @brief Manages loading and providing access to all game data from external files.
     *
     * This class acts as a central repository for game data, such as monster, weapon,
     * and ability templates, preventing hard-coding and making the game easier to
     * expand and balance.
     */
    class DataManager
    {
    public:
        using filePath = std::filesystem::path;

        /**
         * @brief Loads all game data from JSON files in the specified directory.
         * @param dataPath The path to the directory containing the data files.
         */
        void LoadFromFiles(const filePath& dataPath);

        /**
         * @brief Retrieves weapon data by its ID.
         * @param weaponId The ID of the weapon to retrieve.
         * @return A pointer to the WeaponData, or nullptr if not found.
         */
        const WeaponData* GetWeaponData(std::string_view weaponId) const;

        /**
         * @brief Retrieves monster data by its ID.
         * @param monsterId The ID of the monster to retrieve.
         * @return A pointer to the MonsterData, or nullptr if not found.
         */
        const MonsterData* GetMonsterData(std::string_view monsterId) const;
        
        /**
         * @brief Retrieves a random monster's data.
         * @return A pointer to a random MonsterData, or nullptr if no monsters are loaded.
         */
        const MonsterData* GetRandomMonsterData() const;

        /**
         * @brief Retrieves character class data by its ID.
         * @param classId The ID of the class to retrieve.
         * @return A pointer to the CharacterClass, or nullptr if not found.
         */
        const CharacterClass* GetClass(std::string_view classId) const;

        /**
         * @brief Retrieves ability data by its ID.
         * @param abilityId The ID of the ability to retrieve.
         * @return A pointer to the AbilityData, or nullptr if not found.
         */
        const AbilityData* GetAbilityData(std::string_view abilityId) const;        

    private:
        /**
         * @brief Loads weapon data from the specified JSON file.
         * @param path The path to the weapons JSON file.
         */
        void LoadWeaponsData(const filePath& path);
        
        /**
         * @brief Loads monster data from the specified JSON file.
         * @param path The path to the monsters JSON file.
         */
        void LoadMonstersData(const filePath& path);
        
        /**
         * @brief Loads character class data from the specified JSON file.
         * @param path The path to the classes JSON file.
         */
        void LoadClassesData(const filePath& path);
        
        /**
         * @brief Loads ability data from the specified JSON file.
         * @param path The path to the abilities JSON file.
         */
        void LoadAbilitiesData(const filePath& path);

        std::map<std::string, WeaponData> m_weaponTemplates;
        std::map<std::string, MonsterData> m_monsterTemplates;
        std::map<std::string, CharacterClass> m_classTemplates;
        std::map<std::string, AbilityData> m_abilityTemplates;

        std::vector<std::string> m_monsterIds;

        static constexpr std::string_view WEAPONS_FILE = "weapons.json";
        static constexpr std::string_view MONSTERS_FILE = "monsters.json";
        static constexpr std::string_view CLASSES_FILE = "classes.json";
        static constexpr std::string_view ABILITIES_FILE = "abilities.json";
    };
}
