link_directories("../gtest")
include_directories("../gtest/include")

add_executable(
        tiny_random_test
        tests.cpp
        primitives_test.cpp
        combinators_test.cpp containers_test.cpp)

target_link_libraries(
        tiny_random_test
        gtest
        tiny_rand)
