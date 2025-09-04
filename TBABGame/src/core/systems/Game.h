#pragma once
#include "core/common/CharacterClass.h"
#include "core/common/Choices.h"
#include "core/entities/Player.h"

#include <memory>
#include <string>

// Forward-declarations
namespace TBAB
{
    class DataManager;
    class ConsoleInput;
}

namespace TBAB
{
    class Game
    {
    public:
        Game(const DataManager& dataManager, ConsoleInput& input);
        void Run();

    private:
        std::unique_ptr<Player> CreateCharacter(const std::string& name, PlayerClassChoice choice);

        const DataManager& m_dataManager;
        ConsoleInput& m_input;
        std::unique_ptr<Player> m_player;
    };
} // namespace TBAB

