#pragma once

#include "core/entities/Creature.h"
#include "core/Weapon.h"
#include <memory>

namespace TBAB
{
    class Player final : public Creature
    {
    public:
        // The player is created with a name, attributes, and a starting weapon.
        Player(std::string name, const int health, Attributes attributes, std::unique_ptr<Weapon> startingWeapon);

        // In the future, we will add methods for leveling up, swapping weapons, etc.
    };
} // namespace TBAB
