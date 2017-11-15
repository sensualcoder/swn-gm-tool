cmake_minimum_required(VERSION 3.9)

project(SwnGmTool)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -ansi -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

option(BUILD_DRIVER "Build driver" ON)
option(BUILD_TESTS "Build tests" ON)

# Configuration lib
include_directories(${PROJECT_SOURCE_DIR}/Configuration/include)
add_subdirectory(Configuration)

# Data Access lib
include_directories(${PROJECT_SOURCE_DIR}/DataAccess/include)
add_subdirectory(DataAccess)

# Dice Roll lib
include_directories(${PROJECT_SOURCE_DIR}/DiceRoll/include)
add_subdirectory(DiceRoll)

# Hex Grid lib
include_directories(${PROJECT_SOURCE_DIR}/HexGrid/include)
add_subdirectory(HexGrid)

# Faction Control lib
include_directories(${PROJECT_SOURCE_DIR}/FactionControl/include)
add_subdirectory(FactionControl)

# Model headers
include_directories(${PROJECT_SOURCE_DIR}/Models/include)

# Sector Generator lib
include_directories(${PROJECT_SOURCE_DIR}/SectorGen/include)
add_subdirectory(SectorGen)

# SGT (Driver)
include_directories(${PROJECT_SOURCE_DIR}/SGT/include)
add_subdirectory(SGT)

# Tests
if(BUILD_TESTS)
    add_subdirectory(Tests)
endif(BUILD_TESTS)

if(BUILD_DRIVER)
    # Add all extra libs
    set(EXTRA_LIBS ${EXTRA_LIBS} Configuration DataAccess DiceRoll HexGrid FactionControl SectorGen SGT)

    include_directories(${PROJECT_SOURCE_DIR}/include)
    set(SOURCES main.cpp)

    add_executable(SwnGmTool ${SOURCES})
    target_link_libraries(SwnGmTool ${EXTRA_LIBS})
endif(BUILD_DRIVER)

file(COPY conf.json DESTINATION .)
