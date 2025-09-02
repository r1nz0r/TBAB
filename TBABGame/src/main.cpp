#include "core/DataManager.h"
#include "core/GameIds.h"

#include <iostream>
#include <filesystem>

#include "core/Weapon.h"
#include "core/entities/Monster.h"

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

    auto sword = dataManager.CreateWeapon("WEAPON_DAGGER");
    
    if (sword)
    {
        std::cout << "Successfully created a test weapon: " << sword->GetName() << "\n";
    }

    auto skeleton = dataManager.CreateMonster(TBAB::MonsterId::MONSTER_DRAGON);
    if (skeleton)
    {
        std::cout << "Created: " << skeleton->GetName() << "\n";
        std::cout << "Health: " << skeleton->GetCurrentHealth() << "/" << skeleton->GetMaxHealth() << "\n";
        std::cout << "Calculated Damage: " << skeleton->CalculateDamage() << "\n";
    }

    return 0;
}
