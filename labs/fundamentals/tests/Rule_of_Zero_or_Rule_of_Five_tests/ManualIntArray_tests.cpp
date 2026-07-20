//
// Created by marks on 16.07.2026.
//

#include <gtest/gtest.h>
#include "labs/fundamentals/Rule_of_Zero_or_Rule_of_Five/ManualIntArray.h"

TEST(ManualIntArray, CopyConstructorCreatesIndependentCopy){
    ManualIntArray original{3};

    original[0] = 10;
    original[1] = 20;
    original[2] = 30;

    ManualIntArray copy = original;

    copy[0] = 999;

    EXPECT_EQ(original[0], 10);
    EXPECT_EQ(copy[0], 999);
}

TEST(ManualIntArray, MoveConstructorTransfersOwnership) {
    ManualIntArray source{3};

    source[0] = 10;

    ManualIntArray destination{std::move(source)};

    EXPECT_EQ(destination.Size(), 3u);
    EXPECT_EQ(destination[0], 10);

    EXPECT_EQ(source.Size(), 0u);
    EXPECT_EQ(source.Data(), nullptr);
}