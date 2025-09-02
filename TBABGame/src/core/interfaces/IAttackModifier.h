#pragma once

namespace TBAB
{
    class Creature;

    /**
     * @interface IAttackModifier
     * @brief An interface for abilities that are applied when a creature performs an attack.
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
         */
        virtual void ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const = 0;
    };
} // namespace TBAB
