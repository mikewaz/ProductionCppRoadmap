cmake_minimum_required(VERSION 4.1)

project(ProductionCppRoadmap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

if (BUILD_TESTING)
    include(FetchContent)

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    )

    FetchContent_MakeAvailable(googletest)
endif()

add_subdirectory(labs/fundamentals)

add_executable(ProductionCppRoadmap
        main.cpp
)

target_link_libraries(ProductionCppRoadmap PRIVATE
        roadmap_fundamentals
)