#pragma once

#include "nlohmann/json.hpp"
#include <string>
#include <map>
#include <memory>
#include <filesystem> 
#include <string_view>

namespace TBAB
{
    class Weapon;
    class Monster;
}

namespace TBAB
{
    class DataManager
    {
    public:
        void LoadWeaponsData(std::filesystem::path::iterator::reference path);
        void LoadMonstersData(std::filesystem::path::iterator::reference path);
        void LoadFromFiles(const std::filesystem::path& dataPath);
        
        std::unique_ptr<Weapon> CreateWeapon(std::string_view weaponId) const;
        std::unique_ptr<Monster> CreateMonster(std::string_view monsterId) const;


    private:
        nlohmann::json m_weaponTemplates;
        nlohmann::json m_monsterTemplates;
    };
}

