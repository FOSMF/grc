cmake_minimum_required(VERSION 3.10)

project(grc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wswitch -O2")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

add_executable(grc ${SOURCES})
target_include_directories(grc PRIVATE libs/spdlog/include)