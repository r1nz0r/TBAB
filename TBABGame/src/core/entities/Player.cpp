#include "core/entities/Player.h"
#include <utility>

namespace TBAB
{
    Player::Player(std::string name, Attributes attributes, std::unique_ptr<Weapon> startingWeapon)
        : Creature(std::move(name), attributes, std::move(startingWeapon))
    {
    }
}

