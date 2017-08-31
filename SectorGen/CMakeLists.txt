include_directories(${PROJECT_SOURCE_DIR}/HexGrid/include)

set(SOURCES src/SectorGen.cpp)

add_library(SectorGen SHARED ${SOURCES})