include_directories(${PROJECT_SOURCE_DIR}/DataAccess/include)

set (SOURCES src/ConfigManager.cpp)

add_library(Configuration SHARED ${SOURCES})