#include "AbilityUtils.h"
#include "core/entities/Creature.h"
#include "core/events/EventBus.h"
#include "core/systems/AbilityFactory.h"
#include "core/systems/DataManager.h"
#include <sstream>
#include <variant>

namespace TBAB::AbilityUtils
{
    void AddAbility(Creature& creature, const std::string& abilityId)
    {
        bool abilityAdded = false;
        if (auto attackModifier = AbilityFactory::CreateAttackModifier(abilityId))
        {
            creature.AddAttackModifier(std::move(attackModifier));
            abilityAdded = true;
        }

        if (auto defenseModifier = AbilityFactory::CreateDefenseModifier(abilityId))
        {
            creature.AddDefenseModifier(std::move(defenseModifier));
            abilityAdded = true;
        }

        if (!abilityAdded)
        {
            std::stringstream ss;
            ss << "Warning: Unknown ability ID '" << abilityId << "' for creature '" << creature.GetName() << "'.";
            EventBus::Publish(Events::ErrorMessage{ss.str()});
        }
    }

    void ApplyBonus(Creature& creature, const LevelBonus& bonus, const DataManager& dataManager)
    {
        std::visit(
            [&](auto&& arg)
            {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, AbilityBonus>)
                {
                    AddAbility(creature, arg.abilityId);
                    const auto* abilityData = dataManager.GetAbilityData(arg.abilityId);
                    std::stringstream ss;
                    ss << "You have gained the ability: "
                       << (abilityData ? abilityData->name : arg.abilityId + " (Name not found)!") << "!";
                    EventBus::Publish(Events::GameMessage{ss.str()});
                }
                else if constexpr (std::is_same_v<T, AttributeBonus>)
                {
                    creature.ApplyAttributeBonus(arg);
                    std::stringstream ss;
                    ss << "Your attributes have increased!";
                    EventBus::Publish(Events::GameMessage{ss.str()});
                }
            },
            bonus.bonusData);
    }
}
