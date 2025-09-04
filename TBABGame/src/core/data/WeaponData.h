#pragma once

#include "core/data/Types.h"
#include <string>

namespace TBAB
{
    /**
     * @struct WeaponData
     * @brief A structure representing a weapon's data template.
     *
     * This structure is used to load weapon data from a JSON file, providing a
     * data-driven approach for creating in-game weapons.
     */
    struct WeaponData
    {
        std::string id;
        std::string name;
        int damage;
        DamageType damageType;
    };
}
