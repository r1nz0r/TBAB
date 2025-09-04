#pragma once
#include "core/interfaces/IDefenseModifier.h"

namespace TBAB
{
    /**
     * @class ShieldAbility
     * @brief An ability that reduces incoming damage.
     * * This defense modifier reduces damage taken if the defender's strength
     * is higher than the attacker's strength.
     */
    class ShieldAbility final : public IDefenseModifier
    {
    public:
        static constexpr int DAMAGE_REDUCTION = 3;

        /**
         * @brief Reduces incoming damage if the defender is stronger than the attacker.
         * @param damage The current damage value to be modified.
         * @param attacker The creature that is attacking.
         * @param defender The creature that is receiving the damage.
         * @param turnCount The current turn number in the battle.
         */
        void ModifyDefense(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
}
