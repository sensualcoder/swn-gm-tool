include_directories(${PROJECT_SOURCE_DIR}/Models/include)
include_directories(${PROJECT_SOURCE_DIR}/Utils/include)

set(SOURCES src/DiceRoll.cpp)

add_library(DiceRoll ${SOURCES})