#pragma once
#include <functional>
#include <map>
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
        ~AbilityFactory() = delete;

        static std::unique_ptr<IAttackModifier> CreateAttackModifier(std::string_view abilityId);
        static std::unique_ptr<IDefenseModifier> CreateDefenseModifier(std::string_view abilityId);
        
    private:
        template <typename T>
        using ModifierCreator = std::function<std::unique_ptr<T>()>;
        
        template <typename T>
        using CreatorMap = std::map<std::string_view, ModifierCreator<T>>;

        template <typename T>
        static std::unique_ptr<T> CreateModifier(std::string_view abilityId, const CreatorMap<T>& creators);
    };

}