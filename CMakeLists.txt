cmake_minimum_required(VERSION 3.0.0)
project(confmaster VERSION 0.1.0)

# json
add_subdirectory(lib/json)

add_library(confmaster src/confmaster.cpp)
target_include_directories(confmaster PUBLIC include/)
target_link_libraries(confmaster PUBLIC nlohmann_json)

if(BUILD_EXAMPLE)
    add_subdirectory(example/)
endif(BUILD_EXAMPLE)
