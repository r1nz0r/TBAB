#include "core/systems/Battle.h"
#include "core/systems/DataManager.h"
#include "core/common/GameIds.h"

#include <iostream>
#include <filesystem>

#include "core/weapons/Weapon.h"
#include "core/entities/Monster.h"
#include "core/entities/Player.h"
#include "view/renderers/ConsoleRenderer.h"

std::filesystem::path GetDataDirectory()
{
    std::filesystem::path source_file_path(__FILE__);
    std::filesystem::path src_path = source_file_path.parent_path();
    return src_path / "data";
}

int main()
{
    const std::filesystem::path dataDirectory = GetDataDirectory();
    std::cout << "Looking for data in: " << dataDirectory.string() << std::endl;
    TBAB::DataManager dataManager;
    dataManager.LoadFromFiles(dataDirectory);

    std::cout << "\nGame loaded successfully. Ready to start.\n";

    // auto sword = dataManager.CreateWeapon("WEAPON_DAGGER");
    //
    // if (sword)
    // {
    //     std::cout << "Successfully created a test weapon: " << sword->GetName() << "\n";
    // }
    //
    // auto skeleton = dataManager.CreateMonster(TBAB::MonsterId::MONSTER_GOLEM);
    //
    // if (skeleton)
    // {
    //     std::cout << "Created: " << skeleton->GetName() << "\n";
    //     std::cout << "Health: " << skeleton->GetCurrentHealth() << "/" << skeleton->GetMaxHealth() << "\n";
    //     std::cout << "Drops weapon: " << skeleton->GetDroppedWeaponName() << "\n";
    //     std::cout << "Calculated Damage: " << skeleton->CalculateDamage() << "\n";
    // }

    TBAB::Player player("Hero", 15, {2, 2, 2}, dataManager.CreateWeapon(TBAB::WeaponId::WEAPON_DAGGER));
    auto monster = dataManager.CreateMonster(TBAB::MonsterId::MONSTER_DRAGON);
    auto renderer = TBAB::ConsoleRenderer();
    
    if (monster)
    {
        TBAB::Battle battle(player, *monster, renderer);
        TBAB::BattleResult result = battle.Start();
    }

    return 0;
}
