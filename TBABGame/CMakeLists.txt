set(TARGET_NAME TBABGame)

set(CORE_SYSTEMS_SOURCES
    src/core/systems/Battle.h
    src/core/systems/Battle.cpp
    src/core/systems/DataManager.h
    src/core/systems/DataManager.cpp
)

set(CORE_COMMON_SOURCES
    src/core/common/GameIds.h
    src/core/common/Types.h
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
    src/core/weapons/InnateAttack.h
    src/core/weapons/InnateAttack.cpp
    src/core/weapons/Weapon.h
    src/core/weapons/Weapon.cpp
)

set(CORE_ABILITIES_SOURCES
    src/core/abilities/RageAbility.h
    src/core/abilities/RageAbility.cpp
)

set(CORE_INTERFACES_SOURCES
    src/core/interfaces/IAttackModifier.h
    src/core/interfaces/ICharacterClass.h
    src/core/interfaces/IDamageSource.h
    src/core/interfaces/IDefenseModifier.h
)

set(VIEW_RENDERS_SOURCES
    src/view/interfaces/IRenderer.h
    src/view/renderers/ConsoleRenderer.h
    src/view/renderers/ConsoleRenderer.cpp
)

set(SOURCES
    src/main.cpp
    ${CORE_SYSTEMS_SOURCES}
    ${CORE_COMMON_SOURCES}
    ${CORE_ENTITIES_SOURCES}
    ${CORE_WEAPONS_SOURCES}
    ${CORE_ABILITIES_SOURCES}
    ${CORE_INTERFACES_SOURCES}
	${VIEW_RENDERS_SOURCES}
)

add_executable(${TARGET_NAME} ${SOURCES})
target_include_directories(${TARGET_NAME} PRIVATE src)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
target_link_libraries(${TARGET_NAME} PRIVATE nlohmann_json::nlohmann_json)