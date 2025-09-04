#include "EntityFactory.h"

#include "AbilityFactory.h"
#include "DataManager.h"
#include "core/common/AbilityData.h"
#include "core/common/CharacterClass.h"
#include "core/common/GameIds.h"
#include "core/common/MonsterData.h"
#include "core/common/Random.h"
#include "core/common/WeaponData.h"
#include "core/entities/Monster.h"
#include "core/entities/Player.h"
#include "core/events/EventBus.h"
#include "core/weapons/Weapon.h"

#include <sstream>
#include <variant>

namespace TBAB
{
    EntityFactory::EntityFactory(const DataManager& dataManager) : m_dataManager(dataManager) {}

    std::unique_ptr<Player> EntityFactory::CreatePlayer(const std::string& name, PlayerClassChoice choice) const
    {
        Attributes attrs = {Random::Get(1, 3), Random::Get(1, 3), Random::Get(1, 3)};

        std::string_view classId;
        
        switch (choice)
        {
        case PlayerClassChoice::Rogue:
            classId = ClassId::CLASS_ROGUE;
            break;
        case PlayerClassChoice::Warrior:
            classId = ClassId::CLASS_WARRIOR;
            break;
        case PlayerClassChoice::Barbarian:
            classId = ClassId::CLASS_BARBARIAN;
            break;
        }

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

        for (const auto& bonus : classData->levelBonuses)
        {
            if (bonus.level == 1)
            {
                std::visit(
                    [&](auto&& arg)
                    {
                        using T = std::decay_t<decltype(arg)>;
                        
                        if constexpr (std::is_same_v<T, AbilityBonus>)
                        {
                            bool abilityAdded = false;
                            
                            if (auto attackModifier = AbilityFactory::CreateAttackModifier(arg.abilityId))
                            {
                                player->AddAttackModifier(std::move(attackModifier));
                                abilityAdded = true;
                            }
                            else if (auto defenseModifier = AbilityFactory::CreateDefenseModifier(arg.abilityId))
                            {
                                player->AddDefenseModifier(std::move(defenseModifier));
                                abilityAdded = true;
                            }

                            if (abilityAdded)
                            {
                                const AbilityData* abilityData = m_dataManager.GetAbilityData(arg.abilityId);
                                std::stringstream messageStream;
                                
                                if (abilityData)
                                {
                                    messageStream << "You have gained the ability: " << abilityData->name << "!";
                                }
                                else
                                {
                                    messageStream << "You have gained the ability: " << arg.abilityId << " (Name not found)!";
                                }
                                
                                EventBus::Publish(Events::GameMessage{messageStream.str()});
                            }
                        }
                        else if constexpr (std::is_same_v<T, AttributeBonus>)
                        {
                            // TODO: Logic for attribute bonuses will be added later for level-ups.
                        }
                    },
                    bonus.bonusData);
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
                newMonster->AddAttackModifier(std::move(attackModifier));
            }

            if (auto defenseModifier = AbilityFactory::CreateDefenseModifier(abilityId))
            {
                newMonster->AddDefenseModifier(std::move(defenseModifier));
            }
        }

        return newMonster;
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
