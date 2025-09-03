#pragma once
#include <string>
#include <vector>
#include "core/common/Types.h"
#include "nlohmann/json.hpp"

namespace TBAB
{
    struct LevelBonus
    {
        int level;
        nlohmann::json bonusData;
    };

    class CharacterClass
    {
    public:
        std::string id;
        std::string name;
        int healthPerLevel;
        std::vector<LevelBonus> levelBonuses;
    };
}