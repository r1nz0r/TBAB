#pragma once

#include "core/data/CharacterClass.h"

namespace TBAB
{
    class Creature;
    class DataManager;
}

namespace TBAB::AbilityUtils
{
    /**
     * @brief Applies a level-up bonus to a creature.
     * @param creature The creature to apply the bonus to.
     * @param bonus The bonus data to apply.
     * @param dataManager The data manager to retrieve additional data if needed.
     */
    void ApplyBonus(Creature& creature, const LevelBonus& bonus, const DataManager& dataManager);

    /**
     * @brief Adds an ability to a creature by creating the appropriate modifier.
     * @param creature The creature to add the ability to.
     * @param abilityId The ID of the ability to add.
     */
    void AddAbility(Creature& creature, const std::string& abilityId);
}
