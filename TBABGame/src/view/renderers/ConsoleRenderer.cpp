#include "view/renderers/ConsoleRenderer.h"
#include "core/entities/Creature.h"
#include "core/entities/Player.h"
#include "core/events/EventBus.h"
#include "core/systems/DataManager.h"
#include "view/renderers/AsciiArt.h"
#include "view/renderers/ConsoleColors.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace TBAB
{
    ConsoleRenderer::ConsoleRenderer(const DataManager& dataManager) : m_dataManager(dataManager)
    {
#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
#endif
    }

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
                else if (const auto* e = dynamic_cast<const Events::GameWon*>(&event))
                {
                    this->HandleGameWon(*e);
                }
                else if (const auto* e = dynamic_cast<const Events::GameLost*>(&event))
                {
                    this->HandleGameLost(*e);
                }
            });
    }

    void ConsoleRenderer::HandleBattleStart(const Events::BattleStarted& event)
    {
        std::cout << Colors::BOLD_YELLOW << AsciiArt::BATTLE_START << Colors::RESET << std::endl;
        PrintCreatureInfo(*event.combatant1);
        PrintCreatureInfo(*event.combatant2);
        std::cout << "======================================\n";
    }

    void ConsoleRenderer::HandleTurnStarted(const Events::TurnStarted& event)
    {
        std::cout << "--------------------------------------\n";
        std::cout << Colors::GREY << "Turn #" << event.turnNumber << Colors::RESET << "\n";
        std::cout << Colors::YELLOW << event.attackerName << " attacks " << event.defenderName << "!" << Colors::RESET << "\n";
    }

    void ConsoleRenderer::HandleDamageApplied(const Events::DamageApplied& event)
    {
        std::cout << Colors::BOLD_RED << "HIT! " << Colors::RESET << event.targetName << " takes " << Colors::BOLD_RED << event.damageAmount
                  << Colors::RESET << " damage.\n";

        PrintCompactHealthBar(event.targetName, event.currentHp, event.maxHp);
    }

    void ConsoleRenderer::HandleAttackMissed(const Events::AttackMissed& event)
    {
        std::cout << Colors::CYAN << "MISS! " << Colors::RESET << event.attackerName << "'s attack is dodged by " << event.defenderName
                  << "!\n";
    }

    void ConsoleRenderer::HandleBattleEnded(const Events::BattleEnded& event)
    {
        std::cout << "======================================\n";
        std::cout << Colors::BOLD_GREEN << event.winnerName << " is victorious!" << Colors::RESET << "\n";
        std::cout << "======================================\n\n";
    }

    void ConsoleRenderer::HandleGameMessage(const Events::GameMessage& event)
    {
        if (event.message.find("leveled up") != std::string::npos || event.message.find("You have reached level") != std::string::npos)
        {
            std::cout << Colors::BOLD_GREEN << event.message << Colors::RESET << std::endl;
        }
        else if (event.message.find("You have equipped") != std::string::npos)
        {
            std::cout << Colors::BOLD_CYAN << event.message << Colors::RESET << std::endl;
        }
        else
        {
            std::cout << Colors::CYAN << event.message << Colors::RESET << std::endl;
        }
    }

    void ConsoleRenderer::HandleErrorMessage(const Events::ErrorMessage& event)
    {
        std::cerr << Colors::BOLD_RED << "ERROR: " << event.message << Colors::RESET << std::endl;
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
            std::cout << " > " << Colors::MAGENTA << event.creatureName << " " << abilityData->description << Colors::RESET << "\n";
        }
    }

    void ConsoleRenderer::HandleGameWon(const Events::GameWon& event)
    {
        std::cout << Colors::BOLD_GREEN << AsciiArt::VICTORY << Colors::RESET << std::endl;
        std::cout << Colors::BOLD_GREEN << "CONGRATULATIONS! You have defeated all monsters and won the game!" << Colors::RESET
                  << std::endl;
    }

    void ConsoleRenderer::HandleGameLost(const Events::GameLost& event)
    {
        std::cout << Colors::BOLD_RED << AsciiArt::DEFEAT << Colors::RESET << std::endl;
        std::cout << Colors::BOLD_RED << "\nGAME OVER. You have been defeated." << Colors::RESET << std::endl;
    }

    void ConsoleRenderer::PrintCreatureInfo(const Creature& creature) const
    {
        const auto& attrs = creature.GetAttributes();
        const auto* damageSource = creature.GetDamageSource();

        bool isPlayer = dynamic_cast<const Player*>(&creature) != nullptr;

        std::cout << (isPlayer ? Colors::BOLD_CYAN : Colors::BOLD_RED) << "  " << creature.GetName() << Colors::RESET << "\n";

        if (isPlayer)
        {
            const auto* player = static_cast<const Player*>(&creature);
            std::cout << "  - Level: " << Colors::BOLD_YELLOW << player->GetTotalLevel() << Colors::RESET << " (";
            bool first = true;

            for (const auto& pair : player->GetClassLevels())
            {
                if (!first)
                {
                    std::cout << ", ";
                }

                const auto* classData = m_dataManager.GetClass(pair.first);

                if (classData)
                {
                    std::cout << Colors::WHITE << classData->name << " " << pair.second << Colors::RESET;
                }

                first = false;
            }
            std::cout << ")\n";
        }

        PrintHealthBar(creature.GetCurrentHealth(), creature.GetMaxHealth());

        std::cout << "  - Stats: [" << Colors::RED << "Str:" << attrs.strength << Colors::RESET << " " << Colors::GREEN
                  << "Dex:" << attrs.dexterity << Colors::RESET << " " << Colors::BLUE << "End:" << attrs.endurance << Colors::RESET
                  << "]\n";

        if (damageSource)
        {
            std::cout << "  - Weapon: " << damageSource->GetName() << " (Base Dmg: " << Colors::YELLOW << damageSource->GetBaseDamage()
                      << Colors::RESET << ")\n";
        }
        std::cout << "\n";
    }

    void ConsoleRenderer::PrintHealthBar(int current, int max) const
    {
        constexpr int barWidth = 20;
        const float percentage = max > 0 ? static_cast<float>(current) / max : 0;
        const int filledChars = static_cast<int>(percentage * barWidth);

        const std::string_view color = (percentage > 0.6f)   ? Colors::BOLD_GREEN
                                       : (percentage > 0.3f) ? Colors::BOLD_YELLOW
                                                             : Colors::BOLD_RED;

        std::cout << "  - HP: " << color << "[";
        for (int i = 0; i < barWidth; ++i)
        {
            std::cout << (i < filledChars ? "█" : " ");
        }
        std::cout << "]" << Colors::RESET << " " << current << "/" << max << "\n";
    }

    void ConsoleRenderer::PrintCompactHealthBar(const std::string& name, int current, int max) const
    {
        constexpr int barWidth = 15;
        const float percentage = max > 0 ? static_cast<float>(current) / max : 0;
        const int filledChars = static_cast<int>(percentage * barWidth);

        const std::string_view color = (percentage > 0.6f)   ? Colors::BOLD_GREEN
                                       : (percentage > 0.3f) ? Colors::BOLD_YELLOW
                                                             : Colors::BOLD_RED;

        std::cout << " > " << name << " HP: " << color << "[";
        for (int i = 0; i < barWidth; ++i)
        {
            std::cout << (i < filledChars ? "█" : " ");
        }
        std::cout << "]" << Colors::RESET << " " << current << "/" << max << "\n";
    }

    std::string ConsoleRenderer::DamageTypeToString(DamageType type) const
    {
        switch (type)
        {
        case DamageType::Slashing:
            return "Slashing";
        case DamageType::Piercing:
            return "Piercing";
        case DamageType::Bludgeoning:
            return "Bludgeoning";
        default:
            return "Unknown";
        }
    }

    void ConsoleRenderer::ClearScreen() const
    {
#ifdef _WIN32
        system("cls");
#else
        // ANSI escape code for clearing screen
        std::cout << "\033[2J\033[1;1H";
#endif
    }
} // namespace TBAB
