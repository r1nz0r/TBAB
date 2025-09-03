#pragma once

#include "core/common/Types.h"
#include <string>
#include <vector>

namespace TBAB
{
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
