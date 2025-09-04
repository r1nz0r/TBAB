#pragma once

#include "core/systems/DataManager.h"
#include "core/systems/EntityFactory.h"
#include "core/systems/Game.h"
#include "view/ConsoleInput.h"
#include "view/renderers/ConsoleRenderer.h"

#include <memory>

/**
 * @class GameManager
 * @brief Manages the main game loop and all core systems of the application.
 */
class GameManager
{
public:
    GameManager();
    void Run();

private:
    std::unique_ptr<TBAB::DataManager> m_dataManager;
    std::unique_ptr<TBAB::EntityFactory> m_entityFactory;
    std::unique_ptr<TBAB::ConsoleRenderer> m_renderer;
    std::unique_ptr<TBAB::ConsoleInput> m_input;
    std::unique_ptr<TBAB::Game> m_game;
};
