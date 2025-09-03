#pragma once
#include <string>

namespace TBAB
{
    class Creature;

    /**
     * @interface IRenderer
     * @brief An interface describing all the renderable events in the game.
     * This decouples game logic from any specific rendering implementation (console, graphics, etc.).
     */
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        virtual void RenderBattleStart(const Creature& combatant1, const Creature& combatant2) = 0;
        virtual void RenderTurn(const Creature& attacker, const Creature& defender) = 0;
        virtual void RenderAttackHit(const Creature& defender, int damage) = 0;
        virtual void RenderAttackMiss(const Creature& attacker, const Creature& defender) = 0;
        virtual void RenderCreatureState(const Creature& creature) = 0;
        virtual void RenderBattleEnd(const Creature& winner) = 0;
    };
}
