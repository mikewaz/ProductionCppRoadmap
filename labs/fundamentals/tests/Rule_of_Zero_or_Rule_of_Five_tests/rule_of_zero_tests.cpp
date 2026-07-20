//
// Created by marks on 20.07.2026.
//

#include <gtest/gtest.h>
#include "labs/fundamentals/Rule_of_Zero_or_Rule_of_Five/IntArray.h"

using IntArray = production_cpp::rule_of_zero_or_rule_of_five::IntArray;

static_assert(std::is_copy_constructible_v<IntArray>);
static_assert(std::is_copy_assignable_v<IntArray>);
static_assert(std::is_move_constructible_v<IntArray>);
static_assert(std::is_move_assignable_v<IntArray>);


TEST(RuleOfZeroTest, CreatesArrayWithRequestedSize)
{
    const IntArray array{5};

    EXPECT_EQ(array.Size(), 5u);
}

TEST(RuleOfZeroTest, StoresValues)
{
    IntArray array{3};

    array[0] = 10;
    array[1] = 20;
    array[2] = 30;

    EXPECT_EQ(array[0], 10);
    EXPECT_EQ(array[1], 20);
    EXPECT_EQ(array[2], 30);
}

TEST(RuleOfZeroTest, ReadsValuesThroughConstObject)
{
    IntArray array{1};
    array[0] = 42;

    const IntArray& const_array = array;

    EXPECT_EQ(const_array[0], 42);
}

TEST(RuleOfZeroTest, CopyConstructorCreatesIndependentCopy)
{
    IntArray original{2};
    original[0] = 10;
    original[1] = 20;

    IntArray copy = original;

    copy[0] = 100;

    EXPECT_EQ(original[0], 10);
    EXPECT_EQ(copy[0], 100);

    EXPECT_EQ(original[1], 20);
    EXPECT_EQ(copy[1], 20);
}

TEST(RuleOfZeroTest, CopyAssignmentCreatesIndependentCopy)
{
    IntArray source{2};
    source[0] = 10;
    source[1] = 20;

    IntArray destination{1};
    destination[0] = 99;

    destination = source;

    destination[0] = 100;

    EXPECT_EQ(source.Size(), 2u);
    EXPECT_EQ(destination.Size(), 2u);

    EXPECT_EQ(source[0], 10);
    EXPECT_EQ(destination[0], 100);
}

TEST(RuleOfZeroTest, MoveConstructorTransfersValues)
{
    IntArray source{2};
    source[0] = 10;
    source[1] = 20;

    IntArray destination{std::move(source)};

    EXPECT_EQ(destination.Size(), 2u);
    EXPECT_EQ(destination[0], 10);
    EXPECT_EQ(destination[1], 20);
}