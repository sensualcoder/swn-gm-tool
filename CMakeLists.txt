cmake_minimum_required(VERSION 3.9)
project(SwnGmTool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -ansi -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

option(BUILD_DRIVER "Build driver" ON)
option(BUILD_TESTS "Build tests" ON)

include(GNUInstallDirs)

include_directories(/usr/include)
include_directories(/usr/local/include)

# Data Access headers
include_directories(${PROJECT_SOURCE_DIR}/DataAccess/include)

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

# SwnGmToolAPI
include_directories(${PROJECT_SOURCE_DIR}/SwnGmToolAPI/include)
add_subdirectory(SwnGmToolAPI)

# Driver
include_directories(${PROJECT_SOURCE_DIR}/Driver/include)
add_subdirectory(Driver)

# Tests
if(BUILD_TESTS)
    add_subdirectory(Tests)
endif(BUILD_TESTS)

# Check for external libs
find_package(cereal REQUIRED)
find_package(fmt REQUIRED)
find_package(spdlog CONFIG REQUIRED)

if(BUILD_DRIVER)
    # Add all extra libs
    set(EXTRA_LIBS ${EXTRA_LIBS} DiceRoll HexGrid FactionControl SectorGen SwnGmToolAPI Driver)
    set(EXTRA_LIBS ${EXTRA_LIBS} pthread)

    set(SOURCES main.cpp)

    add_executable(SwnGmTool ${SOURCES})
    target_link_libraries(SwnGmTool ${EXTRA_LIBS})
endif(BUILD_DRIVER)

file(COPY Config/DefaultConfig.json DESTINATION .)
add_custom_target(build-time-make_directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory logs)
