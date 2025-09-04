#include "EntityFactory.h"

#include "AbilityFactory.h"
#include "DataManager.h"
#include "core/utils/Random.h"
#include "core/utils/AbilityUtils.h"
#include "core/data/AbilityData.h"
#include "core/data/CharacterClass.h"
#include "core/data/GameIds.h"
#include "core/data/MonsterData.h"
#include "core/data/WeaponData.h"
#include "core/entities/Monster.h"
#include "core/entities/Player.h"
#include "core/events/EventBus.h"
#include "core/weapons/Weapon.h"

#include <sstream>
#include <variant>

namespace TBAB
{
    EntityFactory::EntityFactory(const DataManager& dataManager) : m_dataManager(dataManager) {}

    std::unique_ptr<Player> EntityFactory::CreatePlayer(const std::string& name, PlayerClassChoice classChoice) const
    {
        Attributes attrs = {Random::Get(1, 3), Random::Get(1, 3), Random::Get(1, 3)};
        std::string_view classId_sv;

        switch (classChoice)
        {
        case PlayerClassChoice::Rogue:
            classId_sv = ClassId::CLASS_ROGUE;
            break;
        case PlayerClassChoice::Warrior:
            classId_sv = ClassId::CLASS_WARRIOR;
            break;
        case PlayerClassChoice::Barbarian:
            classId_sv = ClassId::CLASS_BARBARIAN;
            break;
        }
        std::string classId(classId_sv);

        const CharacterClass* classData = m_dataManager.GetClass(classId);

        if (!classData)
        {
            std::stringstream ss;
            ss << "FATAL: Could not find data for class ID: " << classId;
            EventBus::Publish(Events::ErrorMessage{ss.str()});
            return nullptr;
        }

        std::stringstream ss;
        ss << "You have chosen the path of the " << classData->name << ".";
        EventBus::Publish(Events::GameMessage{ss.str()});

        const int health = attrs.endurance + classData->healthPerLevel;

        auto weapon = CreateWeapon(classData->startingWeaponId);
        auto player = std::make_unique<Player>(name, health, attrs, std::move(weapon));

        player->AddClassLevel(classId);

        for (const auto& bonus : classData->levelBonuses)
        {
            if (bonus.level == 1)
            {
                AbilityUtils::ApplyBonus(*player, bonus, m_dataManager);
            }
        }
        return player;
    }

    std::unique_ptr<Monster> EntityFactory::CreateMonster(std::string_view monsterId) const
    {
        const MonsterData* data = m_dataManager.GetMonsterData(monsterId);

        if (!data)
        {
            std::stringstream ss;
            ss << "Warning: Monster template not found for ID: " << monsterId;
            EventBus::Publish(Events::ErrorMessage{ss.str()});
            return nullptr;
        }

        auto droppedWeapon = CreateWeapon(data->droppedWeaponId);

        if (!droppedWeapon)
        {
            std::stringstream ss;
            ss << "Error: Could not create dropped weapon '" << data->droppedWeaponId << "' for monster '" << monsterId << "'";
            EventBus::Publish(Events::ErrorMessage{ss.str()});
            return nullptr;
        }

        auto newMonster = std::make_unique<Monster>(
            data->name, data->attributes, data->health, data->innateDamage, data->innateDamageType, std::move(droppedWeapon));

        for (const auto& abilityId : data->abilityIds)
        {
            if (auto attackModifier = AbilityFactory::CreateAttackModifier(abilityId))
            {
                newMonster->AddAttackModifier(std::move(attackModifier), abilityId);
            }

            if (auto defenseModifier = AbilityFactory::CreateDefenseModifier(abilityId))
            {
                newMonster->AddDefenseModifier(std::move(defenseModifier), abilityId);
            }
        }

        return newMonster;
    }

    std::unique_ptr<Monster> EntityFactory::CreateRandomMonster() const
    {
        const auto* monsterData = m_dataManager.GetRandomMonsterData();

        if (!monsterData)
        {
            EventBus::Publish(Events::ErrorMessage{"Could not get random monster data. Exiting."});
            return nullptr;
        }

        auto monster = CreateMonster(monsterData->id);
        return monster;
    }

    std::unique_ptr<Weapon> EntityFactory::CreateWeapon(std::string_view weaponId) const
    {
        const WeaponData* data = m_dataManager.GetWeaponData(weaponId);

        if (!data)
        {
            std::stringstream ss;
            ss << "Warning: Weapon template not found for ID: " << weaponId;
            EventBus::Publish(Events::ErrorMessage{ss.str()});
            return nullptr;
        }

        return std::make_unique<Weapon>(data->name, data->damage, data->damageType);
    }

} // namespace TBAB
