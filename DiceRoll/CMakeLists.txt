include_directories(${PROJECT_SOURCE_DIR}/Models/include)

set(SOURCES src/DiceRoll.cpp)

add_library(DiceRoll SHARED ${SOURCES})