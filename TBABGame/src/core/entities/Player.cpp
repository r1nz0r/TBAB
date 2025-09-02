#include "core/entities/Player.h"
#include <utility>

namespace TBAB
{
    Player::Player(std::string name, const int health, Attributes attributes, std::unique_ptr<Weapon> startingWeapon)
        : Creature(std::move(name), health, attributes, std::move(startingWeapon))
    {
    }
} // namespace TBAB
