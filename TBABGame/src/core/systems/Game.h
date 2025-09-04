#pragma once
#include "core/common/Choices.h"
#include "core/entities/Player.h"

#include <memory>
#include <string>

namespace TBAB
{
    class EntityFactory;
    class ConsoleInput;
}

namespace TBAB
{
    class Game
    {
    public:
        Game(const EntityFactory& entityFactory, ConsoleInput& input);
        void Run();

    private:
        const EntityFactory& m_entityFactory;
        ConsoleInput& m_input;
        std::unique_ptr<Player> m_player;
    };
} // namespace TBAB

