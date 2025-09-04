#pragma once

#include "core/systems/DataManager.h"
#include "core/systems/EntityFactory.h"
#include "core/systems/Game.h"
#include "view/ConsoleInput.h"
#include "view/renderers/ConsoleRenderer.h"

#include <memory>

/**
* @class GameManager
* @brief Class that manages the main game loop and all key systems of the application.
* * GameManager initializes all necessary components (data managers, factories, renderers)
* and starts the main game process.
*/
class GameManager
{
public:
    /**
    * @brief Default constructor. Initializes all game subsystems.
    */
    GameManager();

    /**
    * @brief Starts the main game loop.
    * * This method calls the Run() method of the main game object, which
    * contains the logic of the game process.
    */
    void Run();

private:
    std::unique_ptr<TBAB::DataManager> m_dataManager;
    std::unique_ptr<TBAB::EntityFactory> m_entityFactory;
    std::unique_ptr<TBAB::ConsoleRenderer> m_renderer;
    std::unique_ptr<TBAB::ConsoleInput> m_input;
    std::unique_ptr<TBAB::Game> m_game;
};
