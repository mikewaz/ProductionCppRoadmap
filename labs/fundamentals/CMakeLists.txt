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

    add_custom_command(TARGET roadmap_fundamentals POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/tests/RaiiWrapperOverResourceTests/file_handle_open_test.txt"        # Откуда (в папке проекта)
            "$<TARGET_FILE_DIR:roadmap_fundamentals>/file_handle_open_test.txt")                              # Куда (в папку с готовым .exe)

    target_link_libraries(explicit_constructor_tests PRIVATE
            roadmap_fundamentals
            GTest::gtest_main
    )

    include(GoogleTest)

    gtest_discover_tests(explicit_constructor_tests)
endif()