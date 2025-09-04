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
    /**
     * @class AbilityFactory
     * @brief A factory class for creating ability modifier objects.
     *
     * This class centralizes the creation of `IAttackModifier` and `IDefenseModifier`
     * objects based on ability IDs. It follows the factory pattern to decouple
     * the creation of abilities from their usage.
     */
    class AbilityFactory
    {
    public:
        AbilityFactory() = delete;
        AbilityFactory(const AbilityFactory &) = delete;
        AbilityFactory(AbilityFactory &&) = delete;
        AbilityFactory &operator=(const AbilityFactory &) = delete;
        AbilityFactory &operator=(AbilityFactory &&) = delete;
        ~AbilityFactory() = delete;

        /**
         * @brief Creates a unique pointer to an attack modifier.
         * @param abilityId The ID of the attack ability to create.
         * @return A unique pointer to the newly created `IAttackModifier`, or nullptr if the ID is not found.
         */
        static std::unique_ptr<IAttackModifier> CreateAttackModifier(std::string_view abilityId);
        
        /**
         * @brief Creates a unique pointer to a defense modifier.
         * @param abilityId The ID of the defense ability to create.
         * @return A unique pointer to the newly created `IDefenseModifier`, or nullptr if the ID is not found.
         */
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
