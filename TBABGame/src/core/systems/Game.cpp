#include "Game.h"
#include "DataManager.h"
#include "EntityFactory.h"
#include "core/entities/Monster.h"
#include "core/events/EventBus.h"
#include "core/systems/Battle.h"
#include "view/ConsoleInput.h"
#include <iostream>
#include <sstream>

namespace TBAB
{
    Game::Game(const DataManager& dataManager, const EntityFactory& entityFactory, ConsoleInput& input)
        : m_dataManager(dataManager), m_entityFactory(entityFactory), m_input(input)
    {
    }

    void Game::Run()
    {
        EventBus::Publish(Events::GameMessage{"Welcome to the Arena!"});

        const std::string name = m_input.GetPlayerName();
        const PlayerClassChoice choice = m_input.GetPlayerClass();

        m_player = m_entityFactory.CreatePlayer(name, choice);

        if (!m_player)
        {
            EventBus::Publish(Events::ErrorMessage{"Character creation failed. Exiting."});
            return;
        }

        std::stringstream ss;
        ss << "\nYour hero, " << m_player->GetName() << ", is ready! Let the battles begin...";
        EventBus::Publish(Events::GameMessage{ss.str()});

        for (int i = 1; i <= BATTLES_TO_WIN; ++i)
        {
            std::stringstream roundMessage;
            roundMessage << "\n--- ROUND " << i << " of " << BATTLES_TO_WIN << " ---";
            EventBus::Publish(Events::GameMessage{roundMessage.str()});

            const auto* monsterData = m_dataManager.GetRandomMonsterData();
            
            if (!monsterData)
            {
                EventBus::Publish(Events::ErrorMessage{"Could not get random monster data. Exiting."});
                return;
            }

            auto monster = m_entityFactory.CreateMonster(monsterData->id);
            
            if (!monster)
            {
                EventBus::Publish(Events::ErrorMessage{"Failed to create monster. Exiting."});
                return;
            }

            Battle battle(*m_player, *monster);
            const BattleResult result = battle.Start();

            if (result == BattleResult::Combatant2_Won)
            {
                EventBus::Publish(Events::GameMessage{"\nGAME OVER. You have been defeated."});
                return;
            }

            PostBattlePhase(std::move(monster));
        }

        EventBus::Publish(Events::GameMessage{"\nCONGRATULATIONS! You have defeated all monsters and won the game!"});
    }

    void Game::PostBattlePhase(std::unique_ptr<Monster> defeatedMonster)
    {
        m_player->RestoreHealth();
        EventBus::Publish(Events::GameMessage{"Your health has been fully restored."});

        if (m_player->GetLevel() < MAX_LEVEL)
        {
            m_player->LevelUp();
            std::stringstream ss;
            ss << "You have reached level " << m_player->GetLevel() << "!";
            EventBus::Publish(Events::GameMessage{ss.str()});
            // TODO: Apply level up bonuses here in the future
        }

        auto droppedWeapon = defeatedMonster->TakeDroppedWeapon();
        
        if (droppedWeapon)
        {
            const PostBattleChoice choice = m_input.GetPostBattleChoice(m_player->GetDamageSource(), *droppedWeapon);
            
            if (choice == PostBattleChoice::TakeWeapon)
            {
                m_player->EquipWeapon(std::move(droppedWeapon));
                std::stringstream ss;
                ss << "You have equipped the " << m_player->GetDamageSource()->GetName() << ".";
                EventBus::Publish(Events::GameMessage{ss.str()});
            }
        }
    }
} // namespace TBAB

