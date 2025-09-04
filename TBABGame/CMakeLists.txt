set(TARGET_NAME TBABGame)

set(CORE_SYSTEMS_SOURCES
    src/core/systems/Battle.h
    src/core/systems/Battle.cpp
    src/core/systems/DataManager.h
    src/core/systems/DataManager.cpp
    src/core/systems/AbilityFactory.h
    src/core/systems/AbilityFactory.cpp
    src/core/systems/Game.h
    src/core/systems/Game.cpp	
	src/core/systems/EntityFactory.h
    src/core/systems/EntityFactory.cpp
)

set(CORE_EVENTS_SOURCES
    src/core/events/Event.h
    src/core/events/EventBus.h
	src/core/events/EventBus.cpp
)

set(CORE_COMMON_SOURCES
    src/core/common/GameIds.h
    src/core/common/Types.h
	src/core/common/Random.h
	src/core/common/CharacterClass.h
	src/core/common/MonsterData.h
	src/core/common/WeaponData.h
	src/core/common/AbilityData.h
	src/core/common/Choices.h
	src/core/common/AbilityUtils.h
	src/core/common/AbilityUtils.cpp
)

set(CORE_ENTITIES_SOURCES
    src/core/entities/Creature.h
    src/core/entities/Creature.cpp
    src/core/entities/Player.h
    src/core/entities/Player.cpp
    src/core/entities/Monster.h
    src/core/entities/Monster.cpp
)

set(CORE_WEAPONS_SOURCES
    src/core/weapons/Weapon.h
    src/core/weapons/Weapon.cpp
)

set(CORE_ABILITIES_SOURCES
    src/core/abilities/ActionSurgeAbility.h
    src/core/abilities/ActionSurgeAbility.cpp
	src/core/abilities/FireBreathAbility.h
    src/core/abilities/FireBreathAbility.cpp
	src/core/abilities/ImmunityToSlashingAbility.h
    src/core/abilities/ImmunityToSlashingAbility.cpp
	src/core/abilities/PoisonAbility.h
    src/core/abilities/PoisonAbility.cpp
	src/core/abilities/RageAbility.h
    src/core/abilities/RageAbility.cpp
	src/core/abilities/ShieldAbility.h
    src/core/abilities/ShieldAbility.cpp
	src/core/abilities/SneakAttackAbility.h
    src/core/abilities/SneakAttackAbility.cpp
	src/core/abilities/StoneSkinAbility.h
    src/core/abilities/StoneSkinAbility.cpp
	src/core/abilities/VulnerabilityToBludgeoningAbility.h
    src/core/abilities/VulnerabilityToBludgeoningAbility.cpp
	
)

set(CORE_INTERFACES_SOURCES
    src/core/interfaces/IAttackModifier.h
    src/core/interfaces/ICharacterClass.h
    src/core/interfaces/IDamageSource.h
    src/core/interfaces/IDefenseModifier.h
)

set(VIEW_RENDERS_SOURCES
    src/view/renderers/ConsoleRenderer.h
    src/view/renderers/ConsoleRenderer.cpp
	src/view/renderers/ConsoleColors.h
	src/view/renderers/AsciiArt.h
)

set(VIEW_INPUT_SOURCES
    src/view/ConsoleInput.h
    src/view/ConsoleInput.cpp
)

set(SOURCES
    src/main.cpp
    ${CORE_SYSTEMS_SOURCES}
	${CORE_EVENTS_SOURCES}
    ${CORE_COMMON_SOURCES}
    ${CORE_ENTITIES_SOURCES}
    ${CORE_WEAPONS_SOURCES}
    ${CORE_ABILITIES_SOURCES}
    ${CORE_INTERFACES_SOURCES}
	${VIEW_RENDERS_SOURCES}
	${VIEW_INPUT_SOURCES}
)

add_executable(${TARGET_NAME} ${SOURCES})
target_include_directories(${TARGET_NAME} PRIVATE src)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
target_link_libraries(${TARGET_NAME} PRIVATE nlohmann_json::nlohmann_json)