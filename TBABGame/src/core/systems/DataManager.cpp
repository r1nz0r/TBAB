#include "core/systems/DataManager.h"
#include "AbilityFactory.h"
#include "core/common/Random.h"
#include "core/events/EventBus.h"
#include "nlohmann/json.hpp"
#include <functional>
#include <fstream>
#include <sstream>

namespace TBAB
{
    namespace
    {
        template <typename T>
        const T* GetDataFromMap(const std::map<std::string, T>& dataMap, std::string_view id)
        {
            auto it = dataMap.find(std::string(id));
            return (it != dataMap.end()) ? &it->second : nullptr;
        }
    } // namespace

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

    void LoadDataFromFile(const DataManager::filePath& path, const std::function<void(const nlohmann::json&)>& parseEntry,
        const std::string& dataType)
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

            std::stringstream ss;
            ss << "Successfully loaded " << count << " " << dataType << " templates.";
            EventBus::Publish(Events::GameMessage{ss.str()});
        }
        catch (const std::exception& e)
        {
            std::stringstream ss;
            ss << "Error loading " << dataType << " data from '" << path.string() << "': " << e.what();
            EventBus::Publish(Events::ErrorMessage{ss.str()});
        }
    }

    void DataManager::LoadFromFiles(const filePath& dataPath)
    {
        if (!std::filesystem::exists(dataPath))
        {
            std::stringstream ss;
            ss << "FATAL ERROR: Data directory not found at " << dataPath;
            EventBus::Publish(Events::ErrorMessage{ss.str()});
            return;
        }

        LoadWeaponsData(dataPath / WEAPONS_FILE);
        LoadMonstersData(dataPath / MONSTERS_FILE);
        LoadClassesData(dataPath / CLASSES_FILE);
        LoadAbilitiesData(dataPath / ABILITIES_FILE);
    }

    void DataManager::LoadWeaponsData(const filePath& path)
    {
        LoadDataFromFile(
            path,
            [this](const nlohmann::json& entry) {
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
            [this](const nlohmann::json& entry) {
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
                m_monsterIds.push_back(md.id);
            },
            "monster");
    }

    void DataManager::LoadClassesData(const filePath& path)
    {
        LoadDataFromFile(
            path,
            [this](const nlohmann::json& entry) {
                CharacterClass cc;
                cc.id = entry.at("id").get<std::string>();
                cc.name = entry.at("name").get<std::string>();
                cc.healthPerLevel = entry.at("healthPerLevel").get<int>();
                cc.startingWeaponId = entry.at("startingWeaponId").get<std::string>();

                for (const auto& bonusEntry : entry.at("levelBonuses"))
                {
                    LevelBonus lb;
                    lb.level = bonusEntry.at("level").get<int>();

                    if (bonusEntry.contains("ability"))
                    {
                        lb.bonusData.emplace<AbilityBonus>(bonusEntry.at("ability").get<std::string>());
                    }
                    else if (bonusEntry.contains("attributeBonus"))
                    {
                        const auto& attrJson = bonusEntry.at("attributeBonus");
                        lb.bonusData.emplace<AttributeBonus>(AttributeBonus{
                            attrJson.value("strength", 0), attrJson.value("dexterity", 0), attrJson.value("endurance", 0)});
                    }
                    else
                    {
                        std::stringstream ss;
                        ss << "Warning: Unknown bonus type in class '" << cc.id << "'. Bonus data: " << bonusEntry.dump();
                        EventBus::Publish(Events::ErrorMessage{ss.str()});
                        continue;
                    }

                    cc.levelBonuses.push_back(std::move(lb));
                }
                m_classTemplates[cc.id] = cc;
            },
            "class");
    }

    void DataManager::LoadAbilitiesData(const filePath& path)
    {
        LoadDataFromFile(
            path,
            [this](const nlohmann::json& entry)
            {
                AbilityData ad;
                ad.id = entry.at("id").get<std::string>();
                ad.name = entry.at("name").get<std::string>();
                ad.description = entry.at("description").get<std::string>();
                m_abilityTemplates[ad.id] = ad;
            },
            "ability");
    }

    const WeaponData* DataManager::GetWeaponData(std::string_view weaponId) const
    {
        return GetDataFromMap(m_weaponTemplates, weaponId);
    }

    const MonsterData* DataManager::GetMonsterData(std::string_view monsterId) const
    {
        return GetDataFromMap(m_monsterTemplates, monsterId);
    }
    
    const MonsterData* DataManager::GetRandomMonsterData() const
    {
        if (m_monsterIds.empty())
        {
            return nullptr;
        }

        const int randomIndex = Random::Get(0, static_cast<int>(m_monsterIds.size()) - 1);
        const std::string& monsterId = m_monsterIds[randomIndex];
        return GetMonsterData(monsterId);
    }

    const CharacterClass* DataManager::GetClass(std::string_view classId) const
    {
        return GetDataFromMap(m_classTemplates, classId);
    }

    const AbilityData* DataManager::GetAbilityData(std::string_view abilityId) const
    {
        return GetDataFromMap(m_abilityTemplates, abilityId);
    }   
} // namespace TBAB

