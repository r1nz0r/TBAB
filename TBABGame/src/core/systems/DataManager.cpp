#include "core/systems/DataManager.h"

#include "AbilityFactory.h"
#include "core/weapons/Weapon.h"
#include "core/entities/Monster.h"

#include <fstream>
#include <iostream>
#include <functional>

namespace TBAB
{
    static constexpr std::string_view WEAPONS_FILE = "weapons.json";
    static constexpr std::string_view MONSTERS_FILE = "monsters.json";
    static constexpr std::string_view CLASSES_FILE = "classes.json";

    DamageType StringToDamageType(const std::string& str)
    {
        if (str == "Slashing")
            return DamageType::Slashing;
        if (str == "Piercing")
            return DamageType::Piercing;
        if (str == "Bludgeoning")
            return DamageType::Bludgeoning;

        throw std::runtime_error("Unknown damage type: " + str);
    }

    void LoadDataFromFile(
        const DataManager::filePath& path, const std::function<void(const nlohmann::json&)>& parseEntry, const std::string& dataType)
    {
        try
        {
            std::ifstream file(path);

            if (!file.is_open())
                throw std::runtime_error("Could not open file: " + path.string());

            nlohmann::json data = nlohmann::json::parse(file);
            size_t count = 0;

            for (const auto& entry : data)
            {
                parseEntry(entry);
                count++;
            }

            std::cout << "Successfully loaded " << count << " " << dataType << " templates." << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error loading " << dataType << " data from '" << path.string() << "': " << e.what() << std::endl;
        }
    }

    void DataManager::LoadFromFiles(const filePath& dataPath)
    {
        if (!std::filesystem::exists(dataPath))
        {
            std::cerr << "FATAL ERROR: Data directory not found at " << dataPath << std::endl;
            return;
        }

        LoadWeaponsData(dataPath / WEAPONS_FILE);
        LoadMonstersData(dataPath / MONSTERS_FILE);
        LoadClassesData(dataPath / CLASSES_FILE);
    }

    void DataManager::LoadWeaponsData(const filePath& path)
    {
        LoadDataFromFile(
            path,
            [this](const nlohmann::json& entry)
            {
                WeaponData wd;
                wd.id = entry.at("id").get<std::string>();
                wd.name = entry.at("name").get<std::string>();
                wd.damage = entry.at("damage").get<int>();
                wd.damageType = StringToDamageType(entry.at("damageType").get<std::string>());
                m_weaponTemplates[wd.id] = wd;
            },
            "weapon");
    }

    void DataManager::LoadMonstersData(const filePath& path)
    {
        LoadDataFromFile(
            path,
            [this](const nlohmann::json& entry)
            {
                MonsterData md;
                md.id = entry.at("id").get<std::string>();
                md.name = entry.at("name").get<std::string>();
                md.health = entry.at("health").get<int>();
                md.attributes = {entry.at("attributes").at("strength").get<int>(), entry.at("attributes").at("dexterity").get<int>(),
                    entry.at("attributes").at("endurance").get<int>()};
                md.innateDamage = entry.at("damage").get<int>();
                md.innateDamageType = StringToDamageType(entry.at("damageType").get<std::string>());
                md.droppedWeaponId = entry.at("droppedWeaponId").get<std::string>();
                md.abilityIds = entry.at("abilities").get<std::vector<std::string>>();
                m_monsterTemplates[md.id] = md;
            },
            "monster");
    }

    void DataManager::LoadClassesData(const filePath& path)
    {
        LoadDataFromFile(
            path,
            [this](const nlohmann::json& entry)
            {
                CharacterClass cc;
                cc.id = entry.at("id").get<std::string>();
                cc.name = entry.at("name").get<std::string>();
                cc.healthPerLevel = entry.at("healthPerLevel").get<int>();
                for (const auto& bonusEntry : entry.at("levelBonuses"))
                {
                    LevelBonus lb;
                    lb.level = bonusEntry.at("level").get<int>();
                    lb.bonusData = bonusEntry;
                    cc.levelBonuses.push_back(lb);
                }
                m_classTemplates[cc.id] = cc;
            },
            "class");
    }

    const WeaponData* DataManager::GetWeaponData(std::string_view weaponId) const
    {
        auto it = m_weaponTemplates.find(std::string(weaponId));
        return (it != m_weaponTemplates.end()) ? &it->second : nullptr;
    }

    const MonsterData* DataManager::GetMonsterData(std::string_view monsterId) const
    {
        auto it = m_monsterTemplates.find(std::string(monsterId));
        return (it != m_monsterTemplates.end()) ? &it->second : nullptr;
    }

    const CharacterClass* DataManager::GetClass(std::string_view classId) const
    {
        auto it = m_classTemplates.find(std::string(classId));
        return (it != m_classTemplates.end()) ? &it->second : nullptr;
    }

    // --- Фабричные методы ---
    std::unique_ptr<Weapon> DataManager::CreateWeapon(std::string_view weaponId) const
    {
        const WeaponData* data = GetWeaponData(weaponId);
        if (!data)
        {
            std::cerr << "Warning: Weapon template not found for ID: " << weaponId << std::endl;
            return nullptr;
        }
        return std::make_unique<Weapon>(data->name, data->damage, data->damageType);
    }

    std::unique_ptr<Monster> DataManager::CreateMonster(std::string_view monsterId) const
    {
        const MonsterData* data = GetMonsterData(monsterId);
        
        if (!data)
        {
            std::cerr << "Warning: Monster template not found for ID: " << monsterId << std::endl;
            return nullptr;
        }

        auto droppedWeapon = CreateWeapon(data->droppedWeaponId);
        
        if (!droppedWeapon)
        {
            std::cerr << "Error: Could not create dropped weapon '" << data->droppedWeaponId << "' for monster '" << monsterId << "'"
                      << std::endl;
            return nullptr;
        }

        // TODO: Применить способности из data->abilityIds
        auto newMonster = std::make_unique<Monster>(
            data->name, data->attributes, data->health, data->innateDamage, data->innateDamageType, std::move(droppedWeapon));

        for (const auto& abilityId : data->abilityIds)
        {
            if (auto attackModifier = AbilityFactory::CreateAttackModifier(abilityId))
            {
                newMonster->AddAttackModifier(std::move(attackModifier));
            }

            if (auto defenseModifier = AbilityFactory::CreateDefenseModifier(abilityId))
            {
                newMonster->AddDefenseModifier(std::move(defenseModifier));
            }
        }
    }
} // namespace TBAB
