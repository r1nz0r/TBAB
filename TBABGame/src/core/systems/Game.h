#pragma once
#include "core/common/Choices.h"
#include "core/entities/Player.h"

#include <memory>
#include <string>

namespace TBAB
{
    class Monster;
    class DataManager;
    class EntityFactory;
    class ConsoleInput;
}

namespace TBAB
{
    /**
     * @class Game
     * @brief The main class for controlling the game's core logic.
     *
     * This class manages the game flow, including starting new games, handling battle rounds,
     * and managing the player's progression. It relies on other systems like DataManager,
     * EntityFactory, and ConsoleInput to function.
     */
    class Game
    {
    public:
        /**
         * @brief Constructs a new Game object.
         * @param dataManager A constant reference to the DataManager.
         * @param entityFactory A constant reference to the EntityFactory.
         * @param input A reference to the ConsoleInput for user interaction.
         */
        Game(const DataManager& dataManager, const EntityFactory& entityFactory, ConsoleInput& input);
        
        /**
         * @brief Starts the main game loop.
         */
        void Run();
        
        /**
         * @brief Starts a new game session, including character creation.
         */
        void StartNewGame();

    private:
        /**
         * @brief Manages the sequence of battle rounds.
         * @return True if the player wins all battles, false otherwise.
         */
        bool PlayRounds();
        
        /**
         * @brief Announces the start of a new battle round.
         * @param roundNumber The current round number.
         */
        void AnnounceRound(int roundNumber);
        
        /**
         * @brief Handles post-battle logic, such as loot and leveling up.
         * @param defeatedMonster A unique pointer to the monster that was defeated.
         */
        void PostBattlePhase(std::unique_ptr<Monster> defeatedMonster);
        
        /**
         * @brief Handles the logic for a player receiving loot from a defeated monster.
         * @param defeatedMonster A unique pointer to the monster that was defeated.
         */
        void HandleLoot(std::unique_ptr<Monster> defeatedMonster);
        
        /**
         * @brief Manages the player's level-up process.
         */
        void HandleLevelUp();

        const DataManager& m_dataManager;
        const EntityFactory& m_entityFactory;
        ConsoleInput& m_input;
        std::unique_ptr<Player> m_player;

        static constexpr int BATTLES_TO_WIN = 5;
        static constexpr int MAX_TOTAL_LEVEL = 3;
    };
} // namespace TBAB
