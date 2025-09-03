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
#include "core/common/GameIds.h"
#include <functional>
#include <map>

namespace TBAB
{
    using AttackModifierCreator = std::function<std::unique_ptr<IAttackModifier>()>;
    using DefenseModifierCreator = std::function<std::unique_ptr<IDefenseModifier>()>;

    static const std::map<std::string_view, AttackModifierCreator> s_attackCreators = {
        {AbilityId::RAGE, [] { return std::make_unique<RageAbility>(); }},
        {AbilityId::SNEAK_ATTACK, [] { return std::make_unique<SneakAttackAbility>(); }},
        {AbilityId::POISON, [] { return std::make_unique<PoisonAbility>(); }},
        {AbilityId::ACTION_SURGE, [] { return std::make_unique<ActionSurgeAbility>(); }},
        {AbilityId::FIRE_BREATH, [] { return std::make_unique<FireBreathAbility>(); }},
    };

    static const std::map<std::string_view, DefenseModifierCreator> s_defenseCreators = {
        {AbilityId::STONE_SKIN, [] { return std::make_unique<StoneSkinAbility>(); }},
        {AbilityId::VULNERABILITY_TO_BLUDGEONING, [] { return std::make_unique<VulnerabilityToBludgeoningAbility>(); }},
        {AbilityId::IMMUNITY_TO_SLASHING, [] { return std::make_unique<ImmunityToSlashingAbility>(); }},
        {AbilityId::SHIELD, [] { return std::make_unique<ShieldAbility>(); }},
    };


    std::unique_ptr<IAttackModifier>
    AbilityFactory::CreateAttackModifier(std::string_view abilityId)
    {
        auto it = s_attackCreators.find(abilityId);

        if (it != s_attackCreators.end())
        {
            return it->second();
        }

        return nullptr;
    }

    std::unique_ptr<IDefenseModifier> AbilityFactory::CreateDefenseModifier(std::string_view abilityId)
    {
        auto it = s_defenseCreators.find(abilityId);

        if (it != s_defenseCreators.end())
        {
            return it->second();
        }

        return nullptr;
    }
} // namespace TBAB