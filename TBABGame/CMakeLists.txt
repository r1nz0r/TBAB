set(TARGET_NAME TBABGame)

set(SOURCES
    src/main.cpp
	src/core/Types.h
	src/core/Weapon.h
	src/core/Weapon.cpp
	src/core/InnateAttack.h
	src/core/InnateAttack.cpp
	src/core/DataManager.h
	src/core/DataManager.cpp
	src/core/abilities/RageAbility.h
	src/core/abilities/RageAbility.cpp
	src/core/entities/Creature.h	
	src/core/entities/Creature.cpp
	src/core/entities/Player.h	
	src/core/entities/Player.cpp
	src/core/entities/Monster.h	
	src/core/entities/Monster.cpp
	src/core/interfaces/IAttackModifier.h
	src/core/interfaces/ICharacterClass.h
	src/core/interfaces/IDamageSource.h
	src/core/interfaces/IDefenseModifier.h
)

add_executable(${TARGET_NAME} ${SOURCES})
target_include_directories(${TARGET_NAME} PRIVATE src)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
target_link_libraries(${TARGET_NAME} PRIVATE nlohmann_json::nlohmann_json)