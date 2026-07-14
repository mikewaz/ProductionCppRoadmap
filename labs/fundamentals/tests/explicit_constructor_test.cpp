#include <type_traits>
#include <gtest/gtest.h>

#include "labs/fundamentals/explicit_constructor.h"

static_assert(std::is_constructible_v<explicit_constructor, int>);
static_assert(!std::is_convertible_v<int, explicit_constructor>);

static_assert(
    std::is_convertible_v<int, implicit_constructor>,
    "Error: implicit_constructor must support implicit conversion from int!"
    );


int getIdFromObject(implicit_constructor obj) {
    return obj.getId();
}


TEST(ExplicitConstructorP1, StoresId)
{
    const explicit_constructor value{42};
    EXPECT_EQ(value.getId(), 42);
}

TEST(ImplicitConstructorTest, DirectInitialization) {
    implicit_constructor obj(42);
    EXPECT_EQ(obj.getId(), 42);
}

TEST(ImplicitConstructorTest, ImplicitConversionOnFunctionCall) {
    EXPECT_EQ(getIdFromObject(100), 100);
}

TEST(ImplicitConstructorTest, CopyInitialization) {
    implicit_constructor obj = 500;
    EXPECT_EQ(obj.getId(), 500);
}