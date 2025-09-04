#include <filesystem>

#include "core/systems/DataManager.h"
#include "core/systems/EntityFactory.h"
#include "core/systems/Game.h"
#include "view/ConsoleInput.h"
#include "view/renderers/ConsoleRenderer.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

std::filesystem::path GetDataDirectory()
{
    std::filesystem::path source_file_path(__FILE__);
    std::filesystem::path src_path = source_file_path.parent_path();
    return src_path / "data";
}

void SetupConsole()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

int main()
{
    SetupConsole();
    
    TBAB::DataManager dataManager;
    dataManager.LoadFromFiles(GetDataDirectory());

    TBAB::EntityFactory entityFactory(dataManager);

    TBAB::ConsoleRenderer renderer(dataManager);
    renderer.RegisterEventHandlers();

    TBAB::ConsoleInput input;

    TBAB::Game game(dataManager, entityFactory, input);
    game.Run();

    std::cin.get();
    return 0;
}
