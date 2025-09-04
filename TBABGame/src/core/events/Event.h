#pragma once
#include "core/entities/Creature.h"

#include <string>
#include <utility> // For std::move

namespace TBAB::Events
{
    /**
     * @struct Event
     * @brief The base class for all game events.
     *
     * Event objects are published to the EventBus and contain data related to a specific
     * game occurrence, such as a battle starting or damage being applied.
     */
    struct Event
    {
        virtual ~Event() = default;
    };

    /**
     * @struct GameMessage
     * @brief An event for general in-game messages to be displayed to the user.
     */
    struct GameMessage : public Event
    {
        std::string message;
        explicit GameMessage(std::string msg) : message(std::move(msg)) {}
    };

    /**
     * @struct ErrorMessage
     * @brief An event for critical error messages.
     */
    struct ErrorMessage : public Event
    {
        std::string message;
        explicit ErrorMessage(std::string msg) : message(std::move(msg)) {}
    };

    /**
     * @struct BattleStarted
     * @brief An event published when a new battle begins.
     */
    struct BattleStarted : public Event
    {
        const Creature* combatant1;
        const Creature* combatant2;

        BattleStarted(const Creature* c1, const Creature* c2) : combatant1(c1), combatant2(c2) {}
    };

    /**
     * @struct NewGameStarted
     * @brief An event published when the player starts a new game.
     */
    struct NewGameStarted : public Event
    {
    };

    /**
     * @struct GameWon
     * @brief An event published when the player wins the game.
     */
    struct GameWon : public Event
    {
    };

    /**
     * @struct GameLost
     * @brief An event published when the player loses the game.
     */
    struct GameLost : public Event
    {
    };

    /**
     * @struct TurnStarted
     * @brief An event published at the beginning of each turn.
     */
    struct TurnStarted : public Event
    {
        std::string attackerName;
        std::string defenderName;
        int turnNumber;

        TurnStarted(std::string attackerName, std::string defenderName, int turnNumber)
            : attackerName(std::move(attackerName)), defenderName(std::move(defenderName)), turnNumber(turnNumber)
        {
        }
    };

    /**
     * @struct DamageApplied
     * @brief An event published when a creature takes damage.
     */
    struct DamageApplied : public Event
    {
        std::string targetName;
        int damageAmount;
        int currentHp;
        int maxHp;

        DamageApplied(std::string targetName, int damageAmount, int currentHp, int maxHp)
            : targetName(std::move(targetName)), damageAmount(damageAmount), currentHp(currentHp), maxHp(maxHp)
        {
        }
    };

    /**
     * @struct AttackMissed
     * @brief An event published when an attack misses its target.
     */
    struct AttackMissed : public Event
    {
        std::string attackerName;
        std::string defenderName;

        AttackMissed(std::string attackerName, std::string defenderName)
            : attackerName(std::move(attackerName)), defenderName(std::move(defenderName))
        {
        }
    };

    /**
     * @struct BattleEnded
     * @brief An event published when a battle concludes.
     */
    struct BattleEnded : public Event
    {
        std::string winnerName;

        explicit BattleEnded(std::string winnerName) : winnerName(std::move(winnerName)) {}
    };

    /**
     * @struct AbilityTriggered
     * @brief An event published when an ability's effect is triggered during combat.
     */
    struct AbilityTriggered : public Event
    {
        std::string creatureName;
        std::string abilityId;

        AbilityTriggered(std::string creatureName, std::string abilityId)
            : creatureName(std::move(creatureName)), abilityId(std::move(abilityId))
        {
        }
    };

} // namespace TBAB::Events
