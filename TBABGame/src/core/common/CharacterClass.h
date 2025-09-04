#pragma once
#include "core/common/Types.h"
#include <string>
#include <variant>
#include <vector>

namespace TBAB
{
    /**
     * @struct AbilityBonus
     * @brief A structure representing a bonus that grants a specific ability.
     */
    struct AbilityBonus
    {
        std::string abilityId;
    };
    
    using AttributeBonus = Attributes;
    using BonusData = std::variant<AbilityBonus, AttributeBonus>;

    /**
     * @struct LevelBonus
     * @brief A structure linking a character level to a specific bonus.
     */
    struct LevelBonus
    {
        int level;
        BonusData bonusData;
    };

    /**
     * @struct CharacterClass
     * @brief A structure to hold character class data loaded from JSON files.
     */
    struct CharacterClass
    {    
        std::string id;
        std::string name;
        int healthPerLevel;
        std::string startingWeaponId;
        std::vector<LevelBonus> levelBonuses;
    };
} // namespace TBAB

