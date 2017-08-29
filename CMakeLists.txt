project(SwnGmTool)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -ansi -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(${PROJECT_SOURCE_DIR}/ControlLayer/include)
add_subdirectory(ControlLayer)
set(EXTRA_LIBS ${EXTRA_LIBS} ControlLayer)

set(SOURCES driver.cpp)

add_executable(SwnGmTool ${SOURCES})
target_link_libraries(SwnGmTool ControlLayer)