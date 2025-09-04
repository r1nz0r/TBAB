#pragma once
#include "core/interfaces/IAttackModifier.h"

namespace TBAB
{
    /**
     * @class SneakAttackAbility
     * @brief An ability that increases damage if the attacker's dexterity is higher than the target's.
     * * This ability is a Rogue class bonus and allows for extra damage by exploiting stealth and surprise.
     */
    class SneakAttackAbility final : public IAttackModifier
    {
    public:
        static constexpr int DAMAGE_AMPLIFIER = 1;

        /**
         * @brief Increases damage if the attacker's dexterity is greater than the defender's.
         * @param damage The current damage value to be modified.
         * @param attacker The creature that is attacking.
         * @param defender The creature that is being attacked.
         * @param turnCount The current turn number in the battle.
         */
        void ModifyAttack(int& damage, const Creature& attacker, const Creature& defender, int turnCount) const override;
    };
}
