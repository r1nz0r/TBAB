#include "ConsoleInput.h"
#include <iostream>
#include <limits>
#include <map>

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
        int choice = 0;

        while (true)
        {
            std::cout << "\nChoose your class:\n";

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
} // namespace TBAB
