include_directories(${PROJECT_SOURCE_DIR}/DTO/include)
include_directories(${PROJECT_SOURCE_DIR}/HexGrid/include)
include_directories(${PROJECT_SOURCE_DIR}/FactionControl/include)
include_directories(${PROJECT_SOURCE_DIR}/SectorGen/include)

set(SOURCES src/Tests.cpp src/TestHelpers.cpp)

add_library(Tests SHARED ${SOURCES})