project(SwnGmTool)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -ansi -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Faction Control lib
include_directories(${PROJECT_SOURCE_DIR}/FactionControl/include)
add_subdirectory(FactionControl)

# Sector Generator lib
include_directories(${PROJECT_SOURCE_DIR}/SectorGen/include)
add_subdirectory(SectorGen)

# Add all extra libs
set(EXTRA_LIBS ${EXTRA_LIBS} FactionControl SectorGen)

set(SOURCES driver.cpp)

add_executable(SwnGmTool ${SOURCES})
target_link_libraries(SwnGmTool ${EXTRA_LIBS})