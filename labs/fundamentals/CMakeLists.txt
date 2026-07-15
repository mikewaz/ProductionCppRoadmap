add_library(roadmap_fundamentals
        TrackedObject.cpp
        TrackedObject.h
        explicit_constructor.cpp
        explicit_constructor.h
)

target_include_directories(roadmap_fundamentals PUBLIC
        ${PROJECT_SOURCE_DIR}
)

if (BUILD_TESTING)
    add_executable(explicit_constructor_tests
            tests/explicit_constructor_test.cpp
            tests/TrackedObject_test.cpp
            RaiiWrapperOverResource/FileHandle.cpp
            RaiiWrapperOverResource/FileHandle.h
            tests/RaiiWrapperOverResourceTests/FileHandleTests.cpp
    )

    target_link_libraries(explicit_constructor_tests PRIVATE
            roadmap_fundamentals
            GTest::gtest_main
    )

    include(GoogleTest)

    gtest_discover_tests(explicit_constructor_tests)
endif()