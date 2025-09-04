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
    class Game
    {
    public:
        Game(const DataManager& dataManager, const EntityFactory& entityFactory, ConsoleInput& input);
        void Run();

    private:
        void PostBattlePhase(std::unique_ptr<Monster> defeatedMonster);

        const DataManager& m_dataManager;
        const EntityFactory& m_entityFactory;
        ConsoleInput& m_input;
        std::unique_ptr<Player> m_player;

        static constexpr int BATTLES_TO_WIN = 5;
        static constexpr int MAX_LEVEL = 3;
    };
} // namespace TBAB

