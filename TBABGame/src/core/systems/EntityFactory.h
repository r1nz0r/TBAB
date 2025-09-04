#pragma once

#include "core/common/Choices.h"
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
    class EntityFactory
    {
    public:
        EntityFactory(const DataManager& dataManager);

        std::unique_ptr<Player> CreatePlayer(const std::string& name, PlayerClassChoice classChoice) const;
        std::unique_ptr<Monster> CreateMonster(std::string_view monsterId) const;
        std::unique_ptr<Weapon> CreateWeapon(std::string_view weaponId) const;

    private:
        const DataManager& m_dataManager;
    };
} // namespace TBAB
