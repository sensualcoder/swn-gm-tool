cmake_minimum_required(VERSION 3.9)

project(SwnGmTool)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -ansi -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

option(BUILD_TESTS "Build tests" ON)

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

# Tests
if(BUILD_TESTS)
    add_subdirectory(Tests)
endif(BUILD_TESTS)

# Add all extra libs
set(EXTRA_LIBS ${EXTRA_LIBS} DTO HexGrid FactionControl SectorGen)

include_directories(${PROJECT_SOURCE_DIR}/include)
set(SOURCES main.cpp src/SGTMain.cpp)

add_executable(SwnGmTool ${SOURCES})
target_link_libraries(SwnGmTool ${EXTRA_LIBS})