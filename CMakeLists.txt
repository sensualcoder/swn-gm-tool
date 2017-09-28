cmake_minimum_required(VERSION 3.9)

project(SwnGmTool)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -ansi -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

option(BUILD_DRIVER "Build driver" ON)
option(BUILD_TESTS "Build tests" ON)

# Data Access
include_directories(${PROJECT_SOURCE_DIR}/DataAccess/include)
add_subdirectory(DataAccess)

# DTOs
include_directories(${PROJECT_SOURCE_DIR}/DTO/include)
add_subdirectory(DTO)

# Hex Grid lib
include_directories(${PROJECT_SOURCE_DIR}/HexGrid/include)
add_subdirectory(HexGrid)

# Faction Control lib
include_directories(${PROJECT_SOURCE_DIR}/FactionControl/include)
add_subdirectory(FactionControl)

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
    set(EXTRA_LIBS ${EXTRA_LIBS} DataAccess DTO HexGrid FactionControl SectorGen SGT)

    include_directories(${PROJECT_SOURCE_DIR}/include)
    set(SOURCES main.cpp)

    add_executable(SwnGmTool ${SOURCES})
    target_link_libraries(SwnGmTool ${EXTRA_LIBS})
endif(BUILD_DRIVER)