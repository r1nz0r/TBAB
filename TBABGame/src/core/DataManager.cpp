#include "core/DataManager.h"
#include <fstream>
#include <iostream>
#include "Types.h"
#include "Weapon.h"
#include "entities/Monster.h"

namespace TBAB
{
    DamageType StringToDamageType(const std::string& str)
    {
        if (str == "Slashing")
            return DamageType::Slashing;
        if (str == "Piercing")
            return DamageType::Piercing;
        if (str == "Bludgeoning")
            return DamageType::Bludgeoning;
        // Fallback for safety
        return DamageType::Bludgeoning;
    }

    void DataManager::LoadFromFiles(const std::filesystem::path& dataPath)
    {
        if (!std::filesystem::exists(dataPath))
        {
            std::cerr << "Error: Data directory not found at " << dataPath << std::endl;
            return;
        }
        LoadWeaponsData(dataPath);
        LoadMonstersData(dataPath);
    }

    void DataManager::LoadWeaponsData(const std::filesystem::path& dataPath)
    {
        const auto weaponsFilePath = dataPath / "weapons.json";
        try
        {
            std::ifstream weaponsFile(weaponsFilePath);
            if (!weaponsFile.is_open())
            {
                throw std::runtime_error("Could not open weapons.json");
            }
            nlohmann::json weaponsData = nlohmann::json::parse(weaponsFile);
            for (const auto& weapon : weaponsData)
            {
                // We store the entire JSON object for the weapon, keyed by its ID.
                std::string id = weapon.at("id");
                m_weaponTemplates[id] = weapon;
            }
            std::cout << "Successfully loaded " << m_weaponTemplates.size() << " weapon templates." << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error loading weapons data: " << e.what() << std::endl;
        }
    }

    std::unique_ptr<Weapon> DataManager::CreateWeapon(std::string_view weaponId) const
    {
        if (!m_weaponTemplates.contains(weaponId))
        {
            std::cerr << "Warning: Weapon template not found for ID: " << weaponId << std::endl;
            return nullptr;
        }

        try
        {
            const auto& data = m_weaponTemplates.at(std::string(weaponId));
            return std::make_unique<Weapon>(data.at("name").get<std::string>(), data.at("damage").get<int>(),
                StringToDamageType(data.at("damageType").get<std::string>()));
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error creating weapon from ID '" << weaponId << "': " << e.what() << std::endl;
            return nullptr;
        }
    }

    void DataManager::LoadMonstersData(const std::filesystem::path& dataPath)
    {
        const auto monstersFilePath = dataPath / "monsters.json";
        try
        {
            std::ifstream monstersFile(monstersFilePath);
            if (!monstersFile.is_open())
            {
                throw std::runtime_error("Could not open monsters.json");
            }
            nlohmann::json monstersData = nlohmann::json::parse(monstersFile);
            for (const auto& monster : monstersData)
            {
                std::string id = monster.at("id");
                m_monsterTemplates[id] = monster;
            }
            std::cout << "Successfully loaded " << m_monsterTemplates.size() << " monster templates." << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error loading monsters data: " << e.what() << std::endl;
        }
    }

    std::unique_ptr<Monster> DataManager::CreateMonster(std::string_view monsterId) const
    {
        if (!m_monsterTemplates.contains(monsterId))
        {
            std::cerr << "Warning: Monster template not found for ID: " << monsterId << std::endl;
            return nullptr;
        }

        try
        {
            const auto& data = m_monsterTemplates.at(std::string(monsterId));

            std::string droppedWeaponId = data.at("droppedWeaponId").get<std::string>();
            auto droppedWeapon = CreateWeapon(droppedWeaponId);

            if (!droppedWeapon)
            {
                throw std::runtime_error("Failed to create dropped weapon with ID: " + droppedWeaponId);
            }

            return std::make_unique<Monster>(data.at("name").get<std::string>(),
                Attributes{data.at("attributes").at("strength").get<int>(), data.at("attributes").at("dexterity").get<int>(),
                    data.at("attributes").at("endurance").get<int>()},
                data.at("health").get<int>(), data.at("damage").get<int>(), StringToDamageType(data.at("damageType").get<std::string>()),
                std::move(droppedWeapon));
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error creating monster from ID '" << monsterId << "': " << e.what() << std::endl;
            return nullptr;
        }
    }
} // namespace TBAB