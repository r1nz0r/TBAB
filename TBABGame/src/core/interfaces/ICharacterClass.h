#pragma once

namespace TBAB
{
    class Creature;

    /**
     * @interface ICharacterClass
     * @brief Represents a character class template (e.g., Warrior, Rogue)
     * that provides bonuses on level up.
     */
    class ICharacterClass
    {
    public:
        virtual ~ICharacterClass() = default;

        /**
         * @brief Applies all bonuses for a given level to a creature.
         * @param creature The creature to apply bonuses to.
         * @param newLevel The new level in this class.
         */
        virtual void ApplyLevelUpBonuses(Creature& creature, int newLevel) const = 0;
    };
} // namespace TBAB
