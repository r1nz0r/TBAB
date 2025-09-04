#pragma once

namespace TBAB
{
    /**
     * @enum PlayerClassChoice
     * @brief An enumeration of available player classes.
     */
    enum class PlayerClassChoice
    {
        Rogue = 1,
        Warrior = 2,
        Barbarian = 3
    };

    /**
     * @enum PostBattleChoice
     * @brief An enumeration of choices a player can make after a battle.
     */
    enum class PostBattleChoice
    {
        TakeWeapon,
        LeaveWeapon
    };
}
