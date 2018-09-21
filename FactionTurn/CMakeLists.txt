set(SOURCES src/FactionTurn.cpp
            src/Faction.cpp
            src/Subject.cpp)

add_library(FactionTurn SHARED ${SOURCES})

#add_subdirectory(tests)