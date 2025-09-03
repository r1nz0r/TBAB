#include "Battle.h"

#include "core/common/Random.h"
#include "core/entities/Creature.h"
#include "view/interfaces/IRenderer.h"

#include <thread>
#include <chrono>

namespace TBAB
{
    static constexpr int PAUSE_TIME_IN_MS = 1000;
    
    Battle::Battle(Creature& combatant1, Creature& combatant2, IRenderer& renderer) 
        : m_combatant1(combatant1), 
          m_combatant2(combatant2),
          m_renderer(renderer)
    {
        if (combatant1.GetAttributes().dexterity >= combatant2.GetAttributes().dexterity)
        {
            m_attacker = &combatant1;
            m_defender = &combatant2;
        }
        else
        {
            m_attacker = &combatant2;
            m_defender = &combatant1;
        }
    }
    
    BattleResult Battle::Start()
    {
        m_renderer.RenderBattleStart(m_combatant1, m_combatant2);

        while (m_combatant1.IsAlive() && m_combatant2.IsAlive())
        {
            m_renderer.RenderTurn(*m_attacker, *m_defender);

            const int attackerDex = m_attacker->GetAttributes().dexterity;
            const int defenderDex = m_defender->GetAttributes().dexterity;

            const int roll = Random::Get(1, attackerDex + defenderDex);

            if (roll > defenderDex)
            {
                const int damage = m_attacker->CalculateDamage();
                m_defender->TakeDamage(damage);            
                m_renderer.RenderAttackHit(*m_defender, damage);
            }
            else
            {
                m_renderer.RenderAttackMiss(*m_attacker, *m_defender);
            }

            std::swap(m_attacker, m_defender);
            std::this_thread::sleep_for(std::chrono::milliseconds(PAUSE_TIME_IN_MS));
        }

        if (m_combatant1.IsAlive())
        {
            m_renderer.RenderBattleEnd(m_combatant1);
            return BattleResult::Combatant1_Won;
        }
        else
        {
            m_renderer.RenderBattleEnd(m_combatant2);
            return BattleResult::Combatant2_Won;
        }
    }

} // namespace TBAB
