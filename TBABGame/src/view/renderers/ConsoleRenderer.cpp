#include "view/renderers/ConsoleRenderer.h"
#include "core/entities/Creature.h"
#include "core/entities/Player.h"
#include "core/events/EventBus.h"
#include "core/systems/DataManager.h"

#include <iostream>
#include <sstream>

namespace TBAB
{
    ConsoleRenderer::ConsoleRenderer(const DataManager& dataManager) : m_dataManager(dataManager) {}

    void ConsoleRenderer::RegisterEventHandlers()
    {
        EventBus::Subscribe(
            [this](const Events::Event& event)
            {
                if (const auto* e = dynamic_cast<const Events::GameMessage*>(&event))
                {
                    this->HandleGameMessage(*e);
                }
                else if (const auto* e = dynamic_cast<const Events::ErrorMessage*>(&event))
                {
                    this->HandleErrorMessage(*e);
                }
                else if (const auto* e = dynamic_cast<const Events::BattleStarted*>(&event))
                {
                    this->HandleBattleStart(*e);
                }
                else if (const auto* e = dynamic_cast<const Events::TurnStarted*>(&event))
                {
                    this->HandleTurnStarted(*e);
                }
                else if (const auto* e = dynamic_cast<const Events::DamageApplied*>(&event))
                {
                    this->HandleDamageApplied(*e);
                }
                else if (const auto* e = dynamic_cast<const Events::AttackMissed*>(&event))
                {
                    this->HandleAttackMissed(*e);
                }
                else if (const auto* e = dynamic_cast<const Events::BattleEnded*>(&event))
                {
                    this->HandleBattleEnded(*e);
                }
                else if (const auto* e = dynamic_cast<const Events::NewGameStarted*>(&event))
                {
                    this->HandleNewGameStarted(*e);
                }
                else if (const auto* e = dynamic_cast<const Events::AbilityTriggered*>(&event))
                {
                    this->HandleAbilityTriggered(*e);
                }
            });
    }

    void ConsoleRenderer::HandleBattleStart(const Events::BattleStarted& event)
    {
        std::cout << "\n=========================\n";
        std::cout << "    BATTLE BEGINS!    \n";
        std::cout << "=========================\n";
        PrintCreatureInfo(*event.combatant1);
        PrintCreatureInfo(*event.combatant2);
        std::cout << "\n=========================\n";
    }

    void ConsoleRenderer::HandleTurnStarted(const Events::TurnStarted& event)
    {
        std::cout << "-------------------------\n";
        std::cout << event.attackerName << " attacks " << event.defenderName << "!\n";
    }

    void ConsoleRenderer::HandleDamageApplied(const Events::DamageApplied& event)
    {
        std::cout << "HIT! " << event.targetName << " takes " << event.damageAmount << " damage.\n";
        std::cout << " > " << event.targetName << " HP: [" << event.currentHp << "/" << event.maxHp << "]\n";
    }

    void ConsoleRenderer::HandleAttackMissed(const Events::AttackMissed& event)
    {
        std::cout << "MISS! " << event.attackerName << "'s attack is dodged by " << event.defenderName << "!\n";
    }

    void ConsoleRenderer::HandleBattleEnded(const Events::BattleEnded& event)
    {
        std::cout << "=========================\n";
        std::cout << event.winnerName << " is victorious!\n";
        std::cout << "=========================\n\n";
    }

    void ConsoleRenderer::HandleGameMessage(const Events::GameMessage& event)
    {
        std::cout << event.message << std::endl;
    }

    void ConsoleRenderer::HandleErrorMessage(const Events::ErrorMessage& event)
    {
        std::cerr << "ERROR: " << event.message << std::endl;
    }

    void ConsoleRenderer::PrintCreatureInfo(const Creature& creature) const
    {
        const auto& attrs = creature.GetAttributes();
        const auto* damageSource = creature.GetDamageSource();

        std::cout << "  " << creature.GetName() << "\n";

        if (const auto* player = dynamic_cast<const Player*>(&creature))
        {
            std::stringstream ss;
            ss << "  - Level: " << player->GetTotalLevel() << " (";

            bool bIsFirstLevel = true;

            for (const auto& classLevelPair : player->GetClassLevels())
            {
                if (!bIsFirstLevel)
                {
                    ss << ", ";
                }

                const auto* classData = m_dataManager.GetClass(classLevelPair.first);

                if (classData)
                {
                    ss << classData->name << " " << classLevelPair.second;
                }

                bIsFirstLevel = false;
            }

            ss << ")\n";
            std::cout << ss.str();
        }

        std::cout << "  - HP: " << creature.GetCurrentHealth() << "/" << creature.GetMaxHealth() << "\n";
        std::cout << "  - Stats: [Str:" << attrs.strength << " Dex:" << attrs.dexterity << " End:" << attrs.endurance << "]\n";
        if (damageSource)
        {
            std::cout << "  - Weapon: " << damageSource->GetName() << " (Base Dmg: " << damageSource->GetBaseDamage() << ")\n";
        }
        std::cout << "\n";
    }

    void ConsoleRenderer::HandleNewGameStarted(const Events::NewGameStarted& event)
    {
        ClearScreen();
    }

    void ConsoleRenderer::HandleAbilityTriggered(const Events::AbilityTriggered& event)
    {
        const auto* abilityData = m_dataManager.GetAbilityData(event.abilityId);
        
        if (abilityData)
        {
            std::cout << " > " << event.creatureName << " " << abilityData->description << "\n";
        }
    }

    void ConsoleRenderer::ClearScreen() const
    {
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif
    }
} // namespace TBAB
