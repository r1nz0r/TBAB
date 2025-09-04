#pragma once

namespace TBAB
{
    /**
     * @struct Attributes
     * @brief A structure to hold the core attributes of a creature.
     */
    struct Attributes
    {
        int strength;
        int dexterity;
        int endurance;
    };

    /**
     * @enum DamageType
     * @brief An enumeration of available damage types.
     */
    enum class DamageType
    {
        Slashing,
        Piercing,
        Bludgeoning
    };
} // namespace TBAB
