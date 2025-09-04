#pragma once
#include "core/common/Types.h"
#include <string>
#include <variant>
#include <vector>

namespace TBAB
{
    struct AbilityBonus
    {
        std::string abilityId;
    };

    using AttributeBonus = Attributes;
    using BonusData = std::variant<AbilityBonus, AttributeBonus>;

    struct LevelBonus
    {
        int level;
        BonusData bonusData;
    };

    struct CharacterClass
    {    
        std::string id;
        std::string name;
        int healthPerLevel;
        std::string startingWeaponId;
        std::vector<LevelBonus> levelBonuses;
    };
} // namespace TBAB

