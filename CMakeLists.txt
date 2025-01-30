cmake_minimum_required(VERSION 3.10)

project(grc)
set(PROGRAM_VERSION "nightly-dev-2025.01.30-patch-1")
add_definitions(-DPROGRAM_VERSION="${PROGRAM_VERSION}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wswitch -O0 -g")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wswitch -O2")
endif()

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

add_executable(grc ${SOURCES})
target_include_directories(grc PRIVATE libs/spdlog/include)

install(TARGETS grc DESTINATION bin)