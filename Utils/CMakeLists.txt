include_directories(${PROJECT_SOURCE_DIR}/DataAccess/include)
include_directories(${PROJECT_SOURCE_DIR}/Models/include)

set(SOURCES src/AssetCreator.cpp)

add_library(AssetCreator SHARED ${SOURCES})