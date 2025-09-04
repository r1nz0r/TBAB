#include "AbilityFactory.h"

#include "core/abilities/ActionSurgeAbility.h"
#include "core/abilities/FireBreathAbility.h"
#include "core/abilities/ImmunityToSlashingAbility.h"
#include "core/abilities/PoisonAbility.h"
#include "core/interfaces/IAttackModifier.h"
#include "core/interfaces/IDefenseModifier.h"
#include "core/abilities/RageAbility.h"
#include "core/abilities/ShieldAbility.h"
#include "core/abilities/SneakAttackAbility.h"
#include "core/abilities/StoneSkinAbility.h"
#include "core/abilities/VulnerabilityToBludgeoningAbility.h"
#include "core/data/GameIds.h"
#include <map>

namespace TBAB
{
    template <typename T> std::unique_ptr<T> AbilityFactory::CreateModifier(std::string_view abilityId, const CreatorMap<T>& creators)
    {
        auto it = creators.find(abilityId);

        if (it != creators.end())
        {
            return it->second();
        }

        return nullptr;
    }

    std::unique_ptr<IAttackModifier> AbilityFactory::CreateAttackModifier(std::string_view abilityId)
    {
        static const CreatorMap<IAttackModifier> s_attackCreators = {
            {AbilityId::RAGE, [] { return std::make_unique<RageAbility>(); }},
            {AbilityId::SNEAK_ATTACK, [] { return std::make_unique<SneakAttackAbility>(); }},
            {AbilityId::POISON, [] { return std::make_unique<PoisonAbility>(); }},
            {AbilityId::ACTION_SURGE, [] { return std::make_unique<ActionSurgeAbility>(); }},
            {AbilityId::FIRE_BREATH, [] { return std::make_unique<FireBreathAbility>(); }},
        };

        return CreateModifier<IAttackModifier>(abilityId, s_attackCreators);
    }

    std::unique_ptr<IDefenseModifier> AbilityFactory::CreateDefenseModifier(std::string_view abilityId)
    {
        static const CreatorMap<IDefenseModifier> s_defenseCreators = {
            {AbilityId::STONE_SKIN, [] { return std::make_unique<StoneSkinAbility>(); }},
            {AbilityId::VULNERABILITY_TO_BLUDGEONING, [] { return std::make_unique<VulnerabilityToBludgeoningAbility>(); }},
            {AbilityId::IMMUNITY_TO_SLASHING, [] { return std::make_unique<ImmunityToSlashingAbility>(); }},
            {AbilityId::SHIELD, [] { return std::make_unique<ShieldAbility>(); }},
        };

        return CreateModifier<IDefenseModifier>(abilityId, s_defenseCreators);
    }
} // namespace TBAB