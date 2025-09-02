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

    namespace WeaponId
    {
        inline constexpr std::string_view WEAPON_CLUB{"WEAPON_CLUB"};
        inline constexpr std::string_view WEAPON_DAGGER{"WEAPON_DAGGER"};
        inline constexpr std::string_view WEAPON_SWORD{"WEAPON_SWORD"};
        inline constexpr std::string_view WEAPON_AXE{"WEAPON_AXE"};
        inline constexpr std::string_view WEAPON_SPEAR{"WEAPON_SPEAR"};
        inline constexpr std::string_view WEAPON_LEGENDARY_SWORD{"WEAPON_LEGENDARY_SWORD"};
    }
} // namespace TBAB
