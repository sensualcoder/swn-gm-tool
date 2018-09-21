include_directories(${PROJECT_SOURCE_DIR}/FactionTurn/include)

set(TEST_SOURCES FactionTests.cpp)

add_executable(FactionTests ${TEST_SOURCES})
target_link_libraries(FactionTests Catch FactionTurn)
