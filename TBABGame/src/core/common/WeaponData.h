#pragma once

#include "core/common/Types.h"
#include <string>

namespace TBAB
{
    struct WeaponData
    {
        std::string id;
        std::string name;
        int damage;
        DamageType damageType;
    };
}
