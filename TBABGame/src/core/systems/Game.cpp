#include "Game.h"
#include "DataManager.h"
#include "EntityFactory.h"
#include "core/common/AbilityUtils.h"
#include "core/common/GameIds.h"
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
        bool wantsToPlay = true;

        while (wantsToPlay)
        {
            StartNewGame();
            bool playerWonGame = PlayRounds();

            if (playerWonGame)
            {
                EventBus::Publish(Events::GameWon{});
            }
            else
            {
                EventBus::Publish(Events::GameLost{});
            }

            wantsToPlay = m_input.AskToPlayAgain();
        }
    }

    void Game::StartNewGame()
    {
        EventBus::Publish(Events::NewGameStarted{});
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
    }

    bool Game::PlayRounds()
    {
        for (int i = 1; i <= BATTLES_TO_WIN; ++i)
        {
            AnnounceRound(i);

            auto monster = m_entityFactory.CreateRandomMonster();

            if (!monster)
            {
                EventBus::Publish(Events::ErrorMessage{"Failed to create monster. Exiting."});
                return false;
            }

            Battle battle(*m_player, *monster);
            const BattleResult result = battle.Start();

            if (result == BattleResult::Combatant2_Won)
            {
                return false;
            }

            if (i < BATTLES_TO_WIN)
            {
                PostBattlePhase(std::move(monster));
            }
        }
        return true;
    }

    void Game::AnnounceRound(int roundNumber)
    {
        std::stringstream roundMessage;
        roundMessage << "\n--- ROUND " << roundNumber << " of " << BATTLES_TO_WIN << " ---";
        EventBus::Publish(Events::GameMessage{roundMessage.str()});
    }

    void Game::PostBattlePhase(std::unique_ptr<Monster> defeatedMonster)
    {
        HandleLoot(std::move(defeatedMonster));
        HandleLevelUp();

        m_player->RestoreHealth();
        EventBus::Publish(Events::GameMessage{"Your health has been fully restored."});
    }

    void Game::HandleLoot(std::unique_ptr<Monster> defeatedMonster)
    {
        if (auto droppedWeapon = defeatedMonster->TakeDroppedWeapon())
        {
            const IDamageSource* currentWeapon = m_player->GetDamageSource();
            const PostBattleChoice choice = m_input.GetPostBattleChoice(currentWeapon, *droppedWeapon);

            if (choice == PostBattleChoice::TakeWeapon)
            {
                m_player->EquipWeapon(std::move(droppedWeapon));
                std::stringstream ss;
                ss << "You have equipped the " << m_player->GetDamageSource()->GetName() << ".";
                EventBus::Publish(Events::GameMessage{ss.str()});
            }
        }
    }

    void Game::HandleLevelUp()
    {
        if (m_player->GetTotalLevel() >= MAX_TOTAL_LEVEL)
            return;

        EventBus::Publish(Events::GameMessage{"\nCongratulations! You leveled up!"});

        const PlayerClassChoice levelUpChoice = m_input.GetLevelUpClassChoice();
        std::string classToLevelUp;

        switch (levelUpChoice)
        {
        case PlayerClassChoice::Rogue:
            classToLevelUp = ClassId::CLASS_ROGUE;
            break;
        case PlayerClassChoice::Warrior:
            classToLevelUp = ClassId::CLASS_WARRIOR;
            break;
        case PlayerClassChoice::Barbarian:
            classToLevelUp = ClassId::CLASS_BARBARIAN;
            break;
        }

        m_player->AddClassLevel(classToLevelUp);
        const int newLevelInClass = m_player->GetLevelInClass(classToLevelUp);

        std::stringstream ss;
        ss << "You have reached level " << m_player->GetTotalLevel() << "!";
        EventBus::Publish(Events::GameMessage{ss.str()});

        const auto* classData = m_dataManager.GetClass(classToLevelUp);

        if (classData)
        {
            m_player->IncreaseMaxHealth(classData->healthPerLevel);

            for (const auto& bonus : classData->levelBonuses)
            {
                if (bonus.level == newLevelInClass)
                {
                    AbilityUtils::ApplyBonus(*m_player, bonus, m_dataManager);
                }
            }
        }
    }
} // namespace TBAB
