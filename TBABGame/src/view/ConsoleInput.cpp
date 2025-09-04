#include "ConsoleInput.h"

#include "core/weapons/Weapon.h"

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
        std::cout << "\nEnter your hero's name: ";
        std::getline(std::cin, name);

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
            std::cout << prompt;

            for (const auto& pair : s_classNames)
            {
                std::cout << "  " << static_cast<int>(pair.first) << ". " << pair.second << "\n";
            }

            std::cout << "> ";
            std::cin >> choice;

            if (std::cin.fail() || s_classNames.find(static_cast<PlayerClassChoice>(choice)) == s_classNames.end())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number between 1 and " << s_classNames.size() << ".\n";
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
            std::cout << prompt << " (y/n): ";
            std::cin >> choice;
            choice = static_cast<char>(std::tolower(choice));

            if (std::cin.fail() || (choice != 'y' && choice != 'n'))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
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
        return GetYesNoChoice("\nDo you want to play again?");
    }

    PostBattleChoice ConsoleInput::GetPostBattleChoice(const IDamageSource* currentWeapon, const IDamageSource& droppedWeapon)
    {
        std::stringstream prompt;
        if (currentWeapon)
        {
            prompt << "\nYour current weapon: " << currentWeapon->GetName() << " (Damage: " << currentWeapon->GetBaseDamage() << ").";
        }

        prompt << "\nThe defeated monster dropped a " << droppedWeapon.GetName() << " (Damage: " << droppedWeapon.GetBaseDamage() << ").\n";
        prompt << "Do you want to take it?";

        return GetYesNoChoice(prompt.str()) ? PostBattleChoice::TakeWeapon : PostBattleChoice::LeaveWeapon;
    }
} // namespace TBAB
