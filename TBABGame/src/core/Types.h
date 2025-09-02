#pragma once
#include <string_view>

namespace TBAB
{
    struct Attributes
    {
        int strength;
        int dexterity;
        int endurance;
    };

    enum class DamageType
    {
        Slashing,
        Piercing,
        Bludgeoning
    };
} // namespace TBAB
