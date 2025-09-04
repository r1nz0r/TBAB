#pragma once
#include "core/interfaces/IDefenseModifier.h"

namespace TBAB
{
    /**
     * @class StoneSkinAbility
     * @brief An ability that reduces damage taken by the creature's endurance value.
     * * This defense modifier allows a creature to absorb a portion of incoming damage using its endurance stat.
     */
    class StoneSkinAbility final : public IDefenseModifier
    {
    public:

        /**
         * @brief Reduces incoming damage by the amount of the defending creature's endurance.
         * @param damage The current damage value to be modified.
         * @param attacker The creature that is attacking.
         * @param defender The creature that is being attacked.
         * @param turnCount The current turn number in the battle.
         */
        void ModifyDefense(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
}
