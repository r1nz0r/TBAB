#include "GameManager.h"

#include <filesystem>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

std::filesystem::path GetDataDirectory()
{
    std::filesystem::path source_file_path(__FILE__);
    std::filesystem::path parent_path = source_file_path.parent_path();
    return parent_path.parent_path() / "data";
}

GameManager::GameManager()
{
    m_dataManager = std::make_unique<TBAB::DataManager>();
    m_dataManager->LoadFromFiles(GetDataDirectory());

    m_entityFactory = std::make_unique<TBAB::EntityFactory>(*m_dataManager);

    m_input = std::make_unique<TBAB::ConsoleInput>();

    m_renderer = std::make_unique<TBAB::ConsoleRenderer>(*m_dataManager);
    m_renderer->RegisterEventHandlers();

    m_game = std::make_unique<TBAB::Game>(*m_dataManager, *m_entityFactory, *m_input);
}

void GameManager::Run()
{
    m_game->Run();
}
