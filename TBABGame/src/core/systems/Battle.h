#pragma once

namespace TBAB
{
    class Creature;

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
        Battle(Creature& combatant1, Creature& combatant2);
        BattleResult Start();
        void DoTurn();

    private:
        Creature& m_combatant1;
        Creature& m_combatant2;
        Creature* m_attacker;
        Creature* m_defender;

        int m_turnCounter = 1;
    };
}
