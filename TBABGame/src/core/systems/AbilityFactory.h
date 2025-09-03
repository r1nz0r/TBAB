#pragma once
#include <memory>
#include <string_view>

namespace TBAB
{
    class IAttackModifier;
    class IDefenseModifier;
}

namespace TBAB
{
    class AbilityFactory
    {
    public:
        AbilityFactory() = delete;
        AbilityFactory(const AbilityFactory &) = delete;
        AbilityFactory(AbilityFactory &&) = delete;
        AbilityFactory &operator=(const AbilityFactory &) = delete;
        AbilityFactory &operator=(AbilityFactory &&) = delete;

        static std::unique_ptr<IAttackModifier> CreateAttackModifier(std::string_view abilityId);
        static std::unique_ptr<IDefenseModifier> CreateDefenseModifier(std::string_view abilityId);
    };

}