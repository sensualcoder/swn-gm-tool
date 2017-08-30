include_directories(${PROJECT_SOURCE_DIR}/FactionControl/include)
include_directories(${PROJECT_SOURCE_DIR}/SectorGen/include)

set(SOURCES src/TestHelpers.cpp)

add_library(Tests ${SOURCES})