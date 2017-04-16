
add_executable(
        tiny_rand_samples
        main.cpp
        rgb_color.cpp
        rgb_color.h basics.h basics.cpp)

target_link_libraries(tiny_rand_samples tiny_rand)
