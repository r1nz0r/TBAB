#pragma once

namespace TBAB
{
    class Creature;
    class IRenderer; // Forward declaration

    enum class BattleResult
    {
        Combatant1_Won,
        Combatant2_Won,
        Draw
    };
}

namespace TBAB
{
    class Battle
    {
    public:
        // Now constructor takes a renderer to decouple logic from presentation
        Battle(Creature& combatant1, Creature& combatant2, IRenderer& renderer);
        
        // Returns a clear result
        BattleResult Start();

    private:
        Creature& m_combatant1;
        Creature& m_combatant2;
        IRenderer& m_renderer; // Reference to the renderer
        Creature* m_attacker;
        Creature* m_defender;
    };
}
