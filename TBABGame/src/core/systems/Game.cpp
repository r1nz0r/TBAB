#include "Game.h"
#include "DataManager.h"
#include "core/common/CharacterClass.h"
#include "core/common/Random.h"
#include "core/systems/Battle.h"
#include "core/common/GameIds.h"
#include "core/entities/Monster.h"
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
        std::cout << "Welcome to the Arena!\n";

        const std::string name = m_input.GetPlayerName();
        const PlayerClassChoice choice = m_input.GetPlayerClass();

        m_player = CreateCharacter(name, choice);

        if (!m_player)
        {
            std::cout << "Character creation failed. Exiting.\n";
            return;
        }

        std::cout << "\nYour hero, " << m_player->GetName() << ", is ready! Let the battles begin...\n";
        std::cout << "--------------------------------\n";

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
            std::cerr << "FATAL: Could not find data for class ID: " << classId << std::endl;
            return nullptr;
        }

        std::cout << "You have chosen the path of the " << classData->name << ".\n";

        const int health = attrs.endurance + classData->healthPerLevel;

        auto weapon = m_dataManager.CreateWeapon(classData->startingWeaponId);
        auto player = std::make_unique<Player>(name, health, attrs, std::move(weapon));

        for (const auto& bonus : classData->levelBonuses)
        {
            if (bonus.level == 1)
            {
                std::visit(
                    [&player](auto&& arg)
                    {
                        using T = std::decay_t<decltype(arg)>;

                        if constexpr (std::is_same_v<T, AbilityBonus>)
                        {
                            if (auto attackModifier = AbilityFactory::CreateAttackModifier(arg.abilityId))
                            {
                                player->AddAttackModifier(std::move(attackModifier));
                                std::cout << "You have gained the ability: " << arg.abilityId << "!\n";
                            }
                            else if (auto defenseModifier = AbilityFactory::CreateDefenseModifier(arg.abilityId))
                            {
                                player->AddDefenseModifier(std::move(defenseModifier));
                                std::cout << "You have gained the ability: " << arg.abilityId << "!\n";
                            }
                        }
                        else if constexpr (std::is_same_v<T, AttributeBonus>)
                        {
                            //TODO Add attribute bonus logic.
                        }
                    },
                    bonus.bonusData);
            }
        }

        return player;
    }

} // namespace TBAB
