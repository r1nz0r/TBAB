#include <filesystem>

#include "core/systems/DataManager.h"
#include "core/systems/EntityFactory.h"
#include "core/systems/Game.h"
#include "view/ConsoleInput.h"
#include "view/renderers/ConsoleRenderer.h"

#include <iostream>

std::filesystem::path GetDataDirectory()
{
    std::filesystem::path source_file_path(__FILE__);
    std::filesystem::path src_path = source_file_path.parent_path();
    return src_path / "data";
}

int main()
{
    TBAB::DataManager dataManager;
    dataManager.LoadFromFiles(GetDataDirectory());

    TBAB::EntityFactory entityFactory(dataManager);

    TBAB::ConsoleRenderer renderer;
    renderer.RegisterEventHandlers();

    TBAB::ConsoleInput input;

    TBAB::Game game(dataManager, entityFactory, input);
    game.Run();
    
    std::cin.get();
    return 0;
}
