include_directories(${PROJECT_SOURCE_DIR}/HexGrid/include)
include_directories(${PROJECT_SOURCE_DIR}/FactionControl/include)
include_directories(${PROJECT_SOURCE_DIR}/Models/include)
include_directories(${PROJECT_SOURCE_DIR}/SectorGen/include)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

set(TEST_SOURCES src/Tests.cpp src/FactionControlTests.cpp src/SectorGenTests.cpp)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests Catch DiceRoll HexGrid FactionControl SectorGen)
