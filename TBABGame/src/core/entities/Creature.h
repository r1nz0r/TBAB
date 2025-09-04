#pragma once

#include "core/data/Types.h"
#include "core/interfaces/IDamageSource.h"
#include "core/interfaces/IAttackModifier.h"
#include "core/interfaces/IDefenseModifier.h"

#include <string>
#include <memory>
#include <vector>

namespace TBAB
{
    /**
     * @class Creature
     * @brief An abstract base class for any participant in a battle (Player or Monster).
     *
     * This class provides the fundamental attributes, health, and combat mechanics
     * shared by all creatures in the game. It manages damage, health, and a list of
     * attack and defense modifiers.
     */
    class Creature
    {
    public:
        
        /**
         * @brief Constructs a new Creature object.
         * @param name The name of the creature.
         * @param health The starting health of the creature.
         * @param attributes The core attributes (Strength, Dexterity, Endurance) of the creature.
         * @param damageSource A unique pointer to the creature's damage source (e.g., a Weapon).
         */
        Creature(std::string name, const int health, Attributes attributes, std::unique_ptr<IDamageSource> damageSource);
        virtual ~Creature() = default;

        /**
         * @brief Checks if the creature is still alive.
         * @return True if the creature's current health is greater than 0, false otherwise.
         */
        bool IsAlive() const;

        [[nodiscard]] virtual const std::string& GetName() const;
        [[nodiscard]] virtual const Attributes& GetAttributes() const;

        /**
         * @brief Calculates the total damage this creature will deal.
         *
         * The total damage is calculated based on the base damage source and the creature's
         * strength, and is then modified by any active attack modifiers.
         *
         * @param defender The creature that is being attacked.
         * @param turnNumber The current turn in the battle.
         * @return The total calculated damage.
         */
        [[nodiscard]] int CalculateDamage(const Creature& defender, const int turnNumber) const;

        [[nodiscard]] int GetCurrentHealth() const;
        [[nodiscard]] int GetMaxHealth() const;
        [[nodiscard]] const IDamageSource* GetDamageSource() const;

        /**
         * @brief Processes incoming damage to the creature.
         *
         * The incoming damage is modified by all active defense modifiers before being applied
         * to the creature's health.
         *
         * @param damage The initial damage value.
         * @param attacker The creature that is attacking.
         * @param turnNumber The current turn in the battle.
         * @return The final damage value that was applied after all modifications.
         */
        virtual int TakeDamage(int damage, const Creature& attacker, int turnNumber);

        /**
         * @brief Adds a new attack modifier to the creature.
         * @param modifier A unique pointer to the attack modifier.
         * @param abilityId The ID of the ability associated with the modifier.
         */
        void AddAttackModifier(std::unique_ptr<IAttackModifier> modifier, const std::string& abilityId);

        /**
         * @brief Adds a new defense modifier to the creature.
         * @param modifier A unique pointer to the defense modifier.
         * @param abilityId The ID of the ability associated with the modifier.
         */
        void AddDefenseModifier(std::unique_ptr<IDefenseModifier> modifier, const std::string& abilityId);

        /**
         * @brief Applies an attribute bonus to the creature's stats.
         * @param bonus The attributes to add to the creature's current attributes.
         */
        void ApplyAttributeBonus(const Attributes& bonus);

        /**
         * @brief Increases the creature's maximum health.
         * @param amount The amount to increase the maximum health by.
         */
        void IncreaseMaxHealth(int amount);

    protected:
        std::string m_name;
        Attributes m_attributes;
        int m_currentHealth;
        int m_maxHealth;

        std::unique_ptr<IDamageSource> m_damageSource;

        std::vector<std::pair<std::string, std::unique_ptr<IAttackModifier>>> m_attackModifiers;
        std::vector<std::pair<std::string, std::unique_ptr<IDefenseModifier>>> m_defenseModifiers;
    };
} // namespace TBAB
