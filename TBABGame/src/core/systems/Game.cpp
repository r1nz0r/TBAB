#include "Game.h"
#include "DataManager.h"
#include "core/common/CharacterClass.h"
#include "core/common/Random.h"
#include "core/systems/Battle.h"
#include "core/common/GameIds.h"
#include "core/entities/Monster.h"
#include "core/events/EventBus.h"
#include "core/systems/AbilityFactory.h"
#include "view/ConsoleInput.h"
#include <iostream>
#include <variant>

namespace TBAB
{
    struct AbilityBonus;
    Game::Game(const DataManager& dataManager, ConsoleInput& input) : m_dataManager(dataManager), m_input(input) {}

    void Game::Run()
    {
        EventBus::Publish(Events::GameMessage{"Welcome to the Arena!"});

        const std::string name = m_input.GetPlayerName();
        const PlayerClassChoice choice = m_input.GetPlayerClass();

        m_player = CreateCharacter(name, choice);

        if (!m_player)
        {
            EventBus::Publish(Events::ErrorMessage{"Character creation failed. Exiting."});
            return;
        }

        std::stringstream ss;
        ss << "\nYour hero, " << m_player->GetName() << ", is ready! Let the battles begin...";
        EventBus::Publish(Events::GameMessage{ss.str()});

        auto monster = m_dataManager.CreateMonster(MonsterId::MONSTER_SKELETON);
        if (monster)
        {
            Battle battle(*m_player, *monster);
            battle.Start();
        }
    }

    std::unique_ptr<Player> Game::CreateCharacter(const std::string& name, PlayerClassChoice choice)
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

        auto weapon = m_dataManager.CreateWeapon(classData->startingWeaponId);
        auto player = std::make_unique<Player>(name, health, attrs, std::move(weapon));

for (const auto& bonus : classData->levelBonuses)
        {
            if (bonus.level == 1)
            {
                std::visit(
                    [&](auto&& arg) {
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
                            //TODO: Logic for attribute bonuses will be added later for level-ups.
                        }
                    },
                    bonus.bonusData);
            }
        }
        return player;
    }

} // namespace TBAB
