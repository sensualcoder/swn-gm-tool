cmake_minimum_required(VERSION 3.9)
project(SwnGmTool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

option(BUILD_TESTS "Build tests" ON)
option(BUILD_UTILS "Build utilities" ON)

# Check for Linux libraries
include(GNUInstallDirs)
include_directories(/usr/include)
include_directories(/usr/local/include)

# Check for required external libs
find_package(cereal REQUIRED)
find_package(fmt REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# Data Access headers
include_directories(${PROJECT_SOURCE_DIR}/DataAccess/include)

# Dice Roll lib
include_directories(${PROJECT_SOURCE_DIR}/DiceRoll/include)
add_subdirectory(DiceRoll)

# Faction Control lib
include_directories(${PROJECT_SOURCE_DIR}/FactionControl/include)
add_subdirectory(FactionControl)

# Faction Turn lib
include_directories(${PROJECT_SOURCE_DIR}/FactionTurn/include)
add_subdirectory(FactionTurn)

# Hex Grid lib
include_directories(${PROJECT_SOURCE_DIR}/HexGrid/include)
add_subdirectory(HexGrid)

# Model headers
include_directories(${PROJECT_SOURCE_DIR}/Models/include)

# Sector Generator lib
include_directories(${PROJECT_SOURCE_DIR}/SectorGen/include)
add_subdirectory(SectorGen)

# Tests
if(BUILD_TESTS)
    include_directories(${PROJECT_SOURCE_DIR}/Tests/include)
    add_subdirectory(Tests)
endif(BUILD_TESTS)

# Tools
if(BUILD_UTILS)
    include_directories(${PROJECT_SOURCE_DIR}/Utils/include)
    add_subdirectory(Utils)
endif(BUILD_UTILS)

# Add all extra libs
set(EXTRA_LIBS ${EXTRA_LIBS} DiceRoll HexGrid FactionControl SectorGen)
set(EXTRA_LIBS ${EXTRA_LIBS} pthread)

set(SOURCES main.cpp)

add_executable(SwnGmTool ${SOURCES})
target_link_libraries(SwnGmTool ${EXTRA_LIBS})

file(COPY Config/ DESTINATION ./Config)
add_custom_target(build-time-make_directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory logs)
