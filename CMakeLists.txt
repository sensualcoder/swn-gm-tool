cmake_minimum_required(VERSION 3.9)
project(SwnGmTool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

option(BUILD_DRIVER "Build driver" ON)
option(BUILD_TESTS "Build tests" ON)

# Check for Linux libraries
include(GNUInstallDirs)
include_directories(/usr/include)
include_directories(/usr/local/include)

# Check for required external libs
include_directories(${PROJECT_SOURCE_DIR}/include/catch)
include_directories(${PROJECT_SOURCE_DIR}/include/cereal)
include_directories(${PROJECT_SOURCE_DIR}/include/fmt)
include_directories(${PROJECT_SOURCE_DIR}/include/spdlog)

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

# SwnGmToolAPI
include_directories(${PROJECT_SOURCE_DIR}/SwnGmToolAPI/include)
add_subdirectory(SwnGmToolAPI)

# Urils
include_directories(${PROJECT_SOURCE_DIR}/Utils/include)

# Driver
include_directories(${PROJECT_SOURCE_DIR}/Driver/include)
add_subdirectory(Driver)

# Tests
if(BUILD_TESTS)
    include_directories(${PROJECT_SOURCE_DIR}/Tests/include)
    add_subdirectory(Tests)
endif(BUILD_TESTS)

if(BUILD_DRIVER)
    # Add all extra libs
    set(EXTRA_LIBS ${EXTRA_LIBS} DiceRoll HexGrid FactionControl SectorGen SwnGmToolAPI Driver)
    set(EXTRA_LIBS ${EXTRA_LIBS} pthread)

    set(SOURCES main.cpp)

    add_executable(SwnGmTool ${SOURCES})
    target_link_libraries(SwnGmTool ${EXTRA_LIBS})
endif(BUILD_DRIVER)

file(COPY Config/ DESTINATION ./Config)
add_custom_target(build-time-make_directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory logs)
