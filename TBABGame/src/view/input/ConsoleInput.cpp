#include "ConsoleInput.h"

#include "core/weapons/Weapon.h"
#include "view/renderers/ConsoleColors.h"
#include <iostream>
#include <limits>
#include <map>
#include <sstream>

namespace TBAB
{
    static const std::map<PlayerClassChoice, std::string> s_classNames = {
        {PlayerClassChoice::Rogue, "Rogue"}, {PlayerClassChoice::Warrior, "Warrior"}, {PlayerClassChoice::Barbarian, "Barbarian"}};

    std::string ConsoleInput::GetPlayerName()
    {
        std::string name;
        std::cout << "\n" << Colors::WHITE << "Enter your hero's name: " << Colors::GREY;
        std::getline(std::cin, name);
        std::cout << Colors::RESET;

        if (name.empty())
        {
            name = "Hero";
        }

        return name;
    }

    PlayerClassChoice ConsoleInput::GetPlayerClass()
    {
        return GetClassChoiceInternal("\nChoose your class:\n");
    }

    PlayerClassChoice ConsoleInput::GetLevelUpClassChoice()
    {
        return GetClassChoiceInternal("\nChoose a class to level up:\n");
    }

    PlayerClassChoice ConsoleInput::GetClassChoiceInternal(const std::string& prompt)
    {
        int choice = 0;

        while (true)
        {
            std::cout << Colors::BOLD_YELLOW << prompt << Colors::RESET << "\n";

            for (const auto& pair : s_classNames)
            {
                std::cout << Colors::WHITE << "  " << static_cast<int>(pair.first) << ". " << pair.second << "\n";
            }

            std::cout << Colors::GREY << "> ";
            std::cin >> choice;
            std::cout << Colors::RESET;

            if (std::cin.fail() || s_classNames.find(static_cast<PlayerClassChoice>(choice)) == s_classNames.end())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << Colors::BOLD_RED << "Invalid input. Please enter a number between 1 and " << s_classNames.size() << ".\n"
                          << Colors::RESET;
            }
            else
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return static_cast<PlayerClassChoice>(choice);
            }
        }
    }

    bool ConsoleInput::GetYesNoChoice(const std::string& prompt)
    {
        char choice;

        while (true)
        {
            std::cout << Colors::BOLD_YELLOW << prompt << Colors::GREY;
            std::cin >> choice;
            std::cout << Colors::RESET;
            choice = static_cast<char>(std::tolower(choice));

            if (std::cin.fail() || (choice != 'y' && choice != 'n'))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << Colors::BOLD_RED << "Invalid input. Please enter 'y' or 'n'.\n" << Colors::RESET;
            }
            else
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return (choice == 'y');
            }
        }
    }

    bool ConsoleInput::AskToPlayAgain()
    {
        return GetYesNoChoice("\nDo you want to play again?: ");
    }

    PostBattleChoice ConsoleInput::GetPostBattleChoice(const IDamageSource* currentWeapon, const IDamageSource& droppedWeapon)
    {
        std::cout << Colors::WHITE << "\nYour current weapon: " << Colors::YELLOW << currentWeapon->GetName() << Colors::WHITE
                  << " (Damage: " << Colors::YELLOW << currentWeapon->GetBaseDamage() << Colors::WHITE << ")." << Colors::RESET;

        std::cout << Colors::WHITE << "\nThe defeated monster dropped a " << Colors::CYAN << droppedWeapon.GetName() << Colors::WHITE
                  << " (Damage: " << Colors::CYAN << droppedWeapon.GetBaseDamage() << Colors::WHITE << ")." << Colors::RESET;

        return GetYesNoChoice("\nDo you want to take it? (y/n): ") ? PostBattleChoice::TakeWeapon : PostBattleChoice::LeaveWeapon;
    }

} // namespace TBAB
