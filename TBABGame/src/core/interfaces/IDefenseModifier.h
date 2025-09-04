#pragma once

namespace TBAB
{
    class Creature;

    /**
     * @interface IDefenseModifier
     * @brief An interface for abilities that are applied when a creature receives damage.
     *
     * This interface defines the contract for any ability that can modify the incoming
     * damage a defending creature receives. Classes implementing this interface can be
     * added to a creature to alter its defense based on specific conditions.
     */
    class IDefenseModifier
    {
    public:
        virtual ~IDefenseModifier() = default;

        /**
         * @brief Modifies the incoming damage value for the defender.
         * @param damage The current damage value to be modified.
         * @param attacker The creature that is attacking.
         * @param defender The creature that is receiving the damage.
         * @param turnNumber The current turn in battle.
         */
        virtual void ModifyDefense(int& damage, const Creature& attacker, const Creature& defender, const int turnNumber) const = 0;
    };
} // namespace TBAB
