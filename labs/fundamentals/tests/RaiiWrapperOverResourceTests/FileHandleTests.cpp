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