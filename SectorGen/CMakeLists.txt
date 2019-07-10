include_directories(${PROJECT_SOURCE_DIR}/HexGrid/include)
include_directories(${PROJECT_SOURCE_DIR}/Utils/include)

set(SOURCES src/SectorGen.cpp)

add_library(SectorGen ${SOURCES})