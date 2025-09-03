#include "view/renderers/ConsoleRenderer.h"
#include "core/entities/Creature.h"
#include <iostream>

namespace TBAB
{
    void ConsoleRenderer::RenderBattleStart(const Creature& combatant1, const Creature& combatant2)
    {
        std::cout << "\n=========================\n";
        std::cout << "    BATTLE BEGINS!    \n";
        std::cout << "=========================\n";
        std::cout << combatant1.GetName() << " VS " << combatant2.GetName() << "\n\n";
    }

    void ConsoleRenderer::RenderTurn(const Creature& attacker, const Creature& defender)
    {
        std::cout << "-------------------------\n";
        std::cout << attacker.GetName() << " attacks " << defender.GetName() << "!\n";
    }

    void ConsoleRenderer::RenderAttackHit(const Creature& defender, int damage)
    {
        std::cout << "HIT! " << defender.GetName() << " takes " << damage << " damage.\n";
        std::cout << " > " << defender.GetName() << " HP: [" << defender.GetCurrentHealth() << "/" << defender.GetMaxHealth() << "]\n";
    }

    void ConsoleRenderer::RenderAttackMiss(const Creature& attacker, const Creature& defender)
    {
        std::cout << "MISS! " << attacker.GetName() << "'s attack is dodged by " << defender.GetName() << "!\n";
    }

    void ConsoleRenderer::RenderCreatureState(const Creature& creature)
    {
        std::cout << " > " << creature.GetName() << " HP: [" << creature.GetCurrentHealth() << "/" << creature.GetMaxHealth() << "]\n";
    }

    void ConsoleRenderer::RenderBattleEnd(const Creature& winner)
    {
        std::cout << "=========================\n";
        std::cout << winner.GetName() << " is victorious!\n";
        std::cout << "=========================\n\n";
    }
}

