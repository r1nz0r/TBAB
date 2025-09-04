#include "Game.h"
#include "EntityFactory.h"
#include "core/common/GameIds.h"
#include "core/entities/Monster.h"
#include "core/events/EventBus.h"
#include "core/systems/Battle.h"
#include "view/ConsoleInput.h"
#include <iostream>
#include <sstream>

namespace TBAB
{
    Game::Game(const EntityFactory& entityFactory, ConsoleInput& input) : m_entityFactory(entityFactory), m_input(input) {}

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

        auto monster = m_entityFactory.CreateMonster(MonsterId::MONSTER_SKELETON);
        
        if (monster)
        {
            Battle battle(*m_player, *monster);
            battle.Start();
        }
    }

} // namespace TBAB

