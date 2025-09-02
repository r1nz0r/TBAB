#include "core/entities/Monster.h"
#include "core/InnateAttack.h"
#include <utility>

namespace TBAB
{

    Monster::Monster(std::string name, Attributes attributes, int innateDamage,
        DamageType innateDamageType, std::unique_ptr<Weapon> droppedWeapon)
        : Creature(std::move(name), attributes, std::make_unique<InnateAttack>(innateDamage, innateDamageType))
          , m_droppedWeapon(std::move(droppedWeapon))
    {
    }

    const Weapon* Monster::GetDroppedWeapon() const
    {
        return m_droppedWeapon.get();
    }

    void Monster::TakeDamage(int amount)
    {
        //TODO damage to bitch
    }
}