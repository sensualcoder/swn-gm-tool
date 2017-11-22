include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES src/Driver.cpp)

add_library(Driver SHARED ${SOURCES})