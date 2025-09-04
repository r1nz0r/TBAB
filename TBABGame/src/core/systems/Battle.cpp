#include "Battle.h"

#include "core/common/Random.h"
#include "core/entities/Creature.h"
#include "core/events/EventBus.h"

#include <thread>
#include <chrono>

namespace TBAB
{
    static constexpr int PAUSE_TIME_IN_MS = 1000;

    Battle::Battle(Creature& combatant1, Creature& combatant2) : m_combatant1(combatant1), m_combatant2(combatant2)
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
        EventBus::Publish(Events::BattleStarted{&m_combatant1, &m_combatant2});

        while (m_combatant1.IsAlive() && m_combatant2.IsAlive())
        {
            DoTurn();
        }

        auto& winner = m_combatant1.IsAlive() ? m_combatant1 : m_combatant2;
        EventBus::Publish(Events::BattleEnded{winner.GetName()});

        return (&winner == &m_combatant1) ? BattleResult::Combatant1_Won : BattleResult::Combatant2_Won;
    }

    void Battle::DoTurn()
    {
        EventBus::Publish(Events::TurnStarted{m_attacker->GetName(), m_defender->GetName(), m_turnCounter});

        const int attackerDex = m_attacker->GetAttributes().dexterity;
        const int defenderDex = m_defender->GetAttributes().dexterity;
        const int roll = Random::Get(1, attackerDex + defenderDex);

        if (roll > defenderDex)
        {
            int initialDamage = m_attacker->CalculateDamage(*m_defender, m_turnCounter);
            int finalDamage = m_defender->TakeDamage(initialDamage, *m_attacker, m_turnCounter);

            EventBus::Publish(
                Events::DamageApplied{m_defender->GetName(), finalDamage, m_defender->GetCurrentHealth(), m_defender->GetMaxHealth()});
        }
        else
        {
            EventBus::Publish(Events::AttackMissed{m_attacker->GetName(), m_defender->GetName()});
        }

        if (m_defender->IsAlive())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(PAUSE_TIME_IN_MS));
            std::swap(m_attacker, m_defender);
            ++m_turnCounter;
        }
    }

} // namespace TBAB
