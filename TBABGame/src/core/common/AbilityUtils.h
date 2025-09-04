#pragma once

#include "core/common/CharacterClass.h"

namespace TBAB
{
    class Creature;
    class DataManager;
}

namespace TBAB::AbilityUtils
{
    void ApplyBonus(Creature& creature, const LevelBonus& bonus, const DataManager& dataManager);
    void AddAbility(Creature& creature, const std::string& abilityId);
}
