set(SOURCE_FILES prime_server_tests.cpp)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR}/gtest-external/gtest/src/gtest-download/include)

add_executable(automated-tests ${SOURCE_FILES})

target_link_libraries(automated-tests ws2_32 gtest gtest-main)