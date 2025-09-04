#pragma once

#include "core/common/AbilityData.h"
#include "core/common/CharacterClass.h"
#include "core/common/MonsterData.h"
#include "core/common/WeaponData.h"

#include <string>
#include <map>
#include <memory>
#include <filesystem>
#include <string_view>

namespace TBAB
{
    class Weapon;
    class Monster;

    class DataManager
    {
    public:
        using filePath = std::filesystem::path;

        void LoadFromFiles(const filePath& dataPath);

        const WeaponData* GetWeaponData(std::string_view weaponId) const;
        const MonsterData* GetMonsterData(std::string_view monsterId) const;
        const MonsterData* GetRandomMonsterData() const;
        const CharacterClass* GetClass(std::string_view classId) const;
        const AbilityData* GetAbilityData(std::string_view abilityId) const;        

    private:
        void LoadWeaponsData(const filePath& path);
        void LoadMonstersData(const filePath& path);
        void LoadClassesData(const filePath& path);
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
