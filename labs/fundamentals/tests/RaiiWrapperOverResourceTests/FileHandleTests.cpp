//
// Created by marks on 15.07.2026.
//

#include "labs/fundamentals/RaiiWrapperOverResource/FileHandle.h"

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>
#include <filesystem>
#include <iostream>

static_assert(!std::is_copy_constructible_v<FileHandle>);
static_assert(!std::is_copy_assignable_v<FileHandle>);

static_assert(std::is_nothrow_move_constructible_v<FileHandle>);
static_assert(std::is_nothrow_move_assignable_v<FileHandle>);

TEST(FileHandleTest, OpensFile)
{
    const auto path =  std::filesystem::current_path() / "file_handle_open_test.txt";

    {
        const FileHandle file{path.string(), "rb"};

        EXPECT_TRUE(file.IsOpen());
        EXPECT_NE(file.Get(), nullptr);
    } // FileHandle::~FileHandle()
}

TEST(FileHandleTest, ThrowsWhenFileCannotBeOpened)
{
    const auto path = std::filesystem::temp_directory_path() / "directory_that_does_not_exist" / "file.txt";

    EXPECT_THROW(
            FileHandle(path.string(), "rb"),
            std::runtime_error
    );
}

TEST(FileHandleTest, MoveConstructorTransfersOwnership)
{
    const auto path = std::filesystem::current_path() / "file_handle_open_test.txt";

    {
        FileHandle source{path.string(), "rb"};
        std::FILE* original_pointer = source.Get();

        EXPECT_TRUE(source.IsOpen());
        EXPECT_NE(source.Get(), nullptr);

        FileHandle destination{std::move(source)};

        EXPECT_FALSE(source.IsOpen());
        EXPECT_EQ(source.Get(), nullptr);

        EXPECT_TRUE(destination.IsOpen());
        EXPECT_EQ(destination.Get(), original_pointer);
    } // FileHandle::~FileHandle()
}

TEST(FileHandleTest, MoveAssignmentTransfersOwnership)
{
    const auto source_path= std::filesystem::current_path() / "file_handle_open_test.txt";
    const auto destination_path= std::filesystem::current_path() / "file_handle_destination.txt";

    {
        FileHandle source{source_path.string(), "rb"};
        FileHandle destination{destination_path.string(), "wb"};

        std::FILE* source_pointer = source.Get();

        destination = std::move(source);

        EXPECT_FALSE(source.IsOpen());
        EXPECT_EQ(source.Get(), nullptr);

        EXPECT_TRUE(destination.IsOpen());
        EXPECT_EQ(destination.Get(), source_pointer);
    }

    std::error_code error;
    std::filesystem::remove(destination_path, error);

    EXPECT_FALSE(error.value());
}