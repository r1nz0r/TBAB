#pragma once
#include "view/interfaces/IRenderer.h"

namespace TBAB
{
    /**
     * @class ConsoleRenderer
     * @brief A concrete implementation of IRenderer that outputs battle events to the console.
     */
    class ConsoleRenderer final : public IRenderer
    {
    public:
        void RenderBattleStart(const Creature& combatant1, const Creature& combatant2) override;
        void RenderTurn(const Creature& attacker, const Creature& defender) override;
        void RenderAttackHit(const Creature& defender, int damage) override;
        void RenderAttackMiss(const Creature& attacker, const Creature& defender) override;
        void RenderCreatureState(const Creature& creature) override;
        void RenderBattleEnd(const Creature& winner) override;
    };
}
