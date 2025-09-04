#pragma once

namespace TBAB
{
    class Creature;

    /**
    * @enum BattleResult
    * @brief An enumeration representing the possible outcomes of a battle.
    */
    enum class BattleResult
    {
        Combatant1_Won,
        Combatant2_Won,
        Draw
    };
}

namespace TBAB
{
    /**
    * @class Battle
    * @brief A class that manages a single battle between two creatures.
    * * The battle is turn-based, with an automatic winner.
    */
    class Battle
    {
    public:
        
        /**
        * @brief The battle constructor.
        * @param combatant1 The first creature.
        * @param combatant2 The second creature.
        */
        Battle(Creature& combatant1, Creature& combatant2);

        /**
        * @brief Starts and conducts the battle until it ends.
        * @return BattleResult The outcome of the battle.
        */
        BattleResult Start();

        /**
        * @brief Performs one turn in the battle.
        */
        void DoTurn();

    private:
        Creature& m_combatant1;
        Creature& m_combatant2;
        Creature* m_attacker;
        Creature* m_defender;

        int m_turnCounter = 1;
    };
}
