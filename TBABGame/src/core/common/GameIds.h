#pragma once

#include <string_view>

namespace TBAB
{
    // This file contains constant string identifiers used to create
    // game objects from the DataManager.
    // They must match the "id" fields in the corresponding .json files.

    namespace WeaponId
    {
        inline constexpr std::string_view WEAPON_CLUB{"WEAPON_CLUB"};
        inline constexpr std::string_view WEAPON_DAGGER{"WEAPON_DAGGER"};
        inline constexpr std::string_view WEAPON_SWORD{"WEAPON_SWORD"};
        inline constexpr std::string_view WEAPON_AXE{"WEAPON_AXE"};
        inline constexpr std::string_view WEAPON_SPEAR{"WEAPON_SPEAR"};
        inline constexpr std::string_view WEAPON_LEGENDARY_SWORD{"WEAPON_LEGENDARY_SWORD"};
    } // namespace WeaponId

    namespace MonsterId
    {
        inline constexpr std::string_view MONSTER_GOBLIN{"MONSTER_GOBLIN"};
        inline constexpr std::string_view MONSTER_SKELETON{"MONSTER_SKELETON"};
        inline constexpr std::string_view MONSTER_SLIME{"MONSTER_SLIME"};
        inline constexpr std::string_view MONSTER_GHOST{"MONSTER_GHOST"};
        inline constexpr std::string_view MONSTER_GOLEM{"MONSTER_GOLEM"};
        inline constexpr std::string_view MONSTER_DRAGON{"MONSTER_DRAGON"};
    } // namespace MonsterId

    namespace ClassId
    {
        inline constexpr std::string_view CLASS_ROGUE{"CLASS_ROGUE"};
        inline constexpr std::string_view CLASS_WARRIOR{"CLASS_WARRIOR"};
        inline constexpr std::string_view CLASS_BARBARIAN{"CLASS_BARBARIAN"};
    } // namespace ClassId

    namespace AbilityId
    {
        inline constexpr std::string_view SNEAK_ATTACK{"SNEAK_ATTACK"};
        inline constexpr std::string_view POISON{"POISON"};
        inline constexpr std::string_view ACTION_SURGE{"ACTION_SURGE"};
        inline constexpr std::string_view SHIELD{"SHIELD"};
        inline constexpr std::string_view RAGE{"RAGE"};
        inline constexpr std::string_view STONE_SKIN{"STONE_SKIN"};
        inline constexpr std::string_view VULNERABILITY_TO_BLUDGEONING{"VULNERABILITY_TO_BLUDGEONING"};
        inline constexpr std::string_view IMMUNITY_TO_SLASHING{"IMMUNITY_TO_SLASHING"};
        inline constexpr std::string_view FIRE_BREATH{"FIRE_BREATH"};
    } // namespace AbilityId

} // namespace TBAB
