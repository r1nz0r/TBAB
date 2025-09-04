#pragma once

namespace TBAB
{
    class Creature;

    /**
     * @interface IAttackModifier
     * @brief An interface for abilities that are applied when a creature performs an attack.
     *
     * This interface defines the contract for any ability that can modify the damage
     * an attacking creature deals. Classes implementing this interface can be
     * added to a creature to alter its attack damage based on specific conditions.
     */
    class IAttackModifier
    {
    public:
        virtual ~IAttackModifier() = default;

        /**
         * @brief Modifies the damage value calculated by the attacker.
         * @param damage The current damage value to be modified.
         * @param attacker The creature that is attacking.
         * @param defender The creature that is being attacked.
         * @param turnCount The current turn in the battle.
         */
        virtual void ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const = 0;
    };
} // namespace TBAB
