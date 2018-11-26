include_directories(${PROJECT_SOURCE_DIR}/HexGrid/include)
include_directories(${PROJECT_SOURCE_DIR}/FactionControl/include)
include_directories(${PROJECT_SOURCE_DIR}/Faction/include)
include_directories(${PROJECT_SOURCE_DIR}/Models/include)
include_directories(${PROJECT_SOURCE_DIR}/SectorGen/include)
include_directories(${PROJECT_SOURCE_DIR}/SwnGmToolAPI/include)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

set(TEST_SOURCES src/Tests.cpp 
    src/FactionAssetMapTests.cpp 
    src/FactionControlTests.cpp 
    src/FactionTests.cpp
    src/FactionTurnTests.cpp
    src/SectorGenTests.cpp 
    src/SwnGmToolAPITests.cpp)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests Catch DiceRoll HexGrid FactionControl FactionTurn SectorGen SwnGmToolAPI)
