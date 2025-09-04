#pragma once

#include "core/data/Types.h"
#include <string>
#include <vector>

namespace TBAB
{
    /**
     * @struct MonsterData
     * @brief A structure to hold monster data loaded from JSON files.
     */
    struct MonsterData
    {
        std::string id;
        std::string name;
        int health;
        Attributes attributes;
        int innateDamage;
        DamageType innateDamageType;
        std::string droppedWeaponId;
        std::vector<std::string> abilityIds;
    };
}
