#include "labs/fundamentals/TrackedObject.h"

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

class TrackedObjectTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        ASSERT_EQ(TrackedObject::Stats().alive, 0u);
        TrackedObject::ResetStats();
    }

    void TearDown() override
    {
        EXPECT_EQ(TrackedObject::Stats().alive, 0u);
    }
};

TEST_F(TrackedObjectTest, ConstructorCreatesObject)
{
    {
        const TrackedObject object{"A"};

        const TrackedObjectStats stats = TrackedObject::Stats();

        EXPECT_EQ(stats.direct_constructions, 1u);
        EXPECT_EQ(stats.copy_constructions, 0u);
        EXPECT_EQ(stats.move_constructions, 0u);
        EXPECT_EQ(stats.alive, 1u);

        EXPECT_EQ(object.Name(), "A");
    }

    const TrackedObjectStats stats = TrackedObject::Stats();

    EXPECT_EQ(stats.destructions, 1u);
    EXPECT_EQ(stats.alive, 0u);
}

TEST_F(TrackedObjectTest, CopyConstructorCreatesIndependentObject)
{
    {
        const TrackedObject original{"A"};
        const TrackedObject copy = original;

        const TrackedObjectStats stats = TrackedObject::Stats();

        EXPECT_EQ(stats.direct_constructions, 1u);
        EXPECT_EQ(stats.copy_constructions, 1u);
        EXPECT_EQ(stats.move_constructions, 0u);
        EXPECT_EQ(stats.alive, 2u);

        EXPECT_EQ(original.Name(), "A");
        EXPECT_EQ(copy.Name(), "A");

        EXPECT_NE(original.Id(), copy.Id());
    }

    EXPECT_EQ(TrackedObject::Stats().destructions, 2u);
}

TEST_F(TrackedObjectTest, MoveConstructorTransfersValueToNewObject)
{
    {
        TrackedObject source{"A"};
        const std::uint64_t source_id = source.Id();

        const TrackedObject destination{std::move(source)};

        const TrackedObjectStats stats = TrackedObject::Stats();

        EXPECT_EQ(stats.direct_constructions, 1u);
        EXPECT_EQ(stats.copy_constructions, 0u);
        EXPECT_EQ(stats.move_constructions, 1u);
        EXPECT_EQ(stats.alive, 2u);

        EXPECT_EQ(destination.Name(), "A");
        EXPECT_TRUE(source.Name().empty());

        EXPECT_EQ(source.Id(), source_id);
        EXPECT_NE(source.Id(), destination.Id());
    }

    EXPECT_EQ(TrackedObject::Stats().destructions, 2u);
}

TEST_F(TrackedObjectTest, CopyAssignmentChangesExistingObject)
{
    {
        const TrackedObject source{"Source"};
        TrackedObject destination{"Destination"};

        const std::uint64_t destination_id = destination.Id();

        destination = source;

        const TrackedObjectStats stats = TrackedObject::Stats();

        EXPECT_EQ(stats.direct_constructions, 2u);
        EXPECT_EQ(stats.copy_constructions, 0u);
        EXPECT_EQ(stats.copy_assignments, 1u);
        EXPECT_EQ(stats.alive, 2u);

        EXPECT_EQ(destination.Name(), "Source");

        // Assignment не создаёт новый объект.
        EXPECT_EQ(destination.Id(), destination_id);
    }

    EXPECT_EQ(TrackedObject::Stats().destructions, 2u);
}

TEST_F(TrackedObjectTest, MoveAssignmentChangesExistingObject)
{
    {
        TrackedObject source{"Source"};
        TrackedObject destination{"Destination"};

        const std::uint64_t destination_id = destination.Id();

        destination = std::move(source);

        const TrackedObjectStats stats = TrackedObject::Stats();

        EXPECT_EQ(stats.direct_constructions, 2u);
        EXPECT_EQ(stats.move_constructions, 0u);
        EXPECT_EQ(stats.move_assignments, 1u);
        EXPECT_EQ(stats.alive, 2u);

        EXPECT_EQ(destination.Name(), "Source");
        EXPECT_TRUE(source.Name().empty());

        EXPECT_EQ(destination.Id(), destination_id);
    }

    EXPECT_EQ(TrackedObject::Stats().destructions, 2u);
}

TEST_F(TrackedObjectTest, ObjectsAreDestroyedInReverseOrder)
{
    {
        const TrackedObject first{"First"};

        {
            const TrackedObject second{"Second"};

            EXPECT_EQ(TrackedObject::Stats().alive, 2u);
        }

        EXPECT_EQ(TrackedObject::Stats().alive, 1u);
        EXPECT_EQ(TrackedObject::Stats().destructions, 1u);
    }

    EXPECT_EQ(TrackedObject::Stats().alive, 0u);
    EXPECT_EQ(TrackedObject::Stats().destructions, 2u);
}

TEST_F(TrackedObjectTest, SelfCopyAssignmentIsSafe)
{
    {
        TrackedObject object{"A"};
        const std::uint64_t original_id = object.Id();

        object = object;

        EXPECT_EQ(object.Id(), original_id);
        EXPECT_EQ(object.Name(), "A");

        EXPECT_EQ(TrackedObject::Stats().copy_assignments, 1u);
        EXPECT_EQ(TrackedObject::Stats().alive, 1u);
    }
}

TEST_F(TrackedObjectTest, MoveOperationsAreNoexcept)
{
    static_assert(
        std::is_nothrow_move_constructible_v<TrackedObject>
    );

    static_assert(
        std::is_nothrow_move_assignable_v<TrackedObject>
    );

    SUCCEED();
}