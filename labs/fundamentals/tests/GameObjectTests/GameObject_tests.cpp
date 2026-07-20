//
// Created by marks on 20.07.2026.
//

#include <gtest/gtest.h>
#include "labs/fundamentals/object_ownership/GameObject.h"

using GameObject = production_cpp::object_ownership::GameObject;

TEST(GameObject, ParentOwnsAddedChild) {
    GameObject root{"root"};

    auto child = std::make_unique<GameObject>("child");
    auto child_address = child.get();
    GameObject &added_child = root.AddChild(std::move(child));

    EXPECT_EQ(child, nullptr);

    EXPECT_EQ(root.ChildCount(), 1);
    EXPECT_EQ(&added_child, child_address);

    EXPECT_EQ(added_child.Name(), "child");
    EXPECT_EQ(added_child.Parent(), &root);
}

TEST(ObjectOwnershipTest, BuildsObjectHierarchy) {
    GameObject root{"Root"};

    GameObject &player = root.AddChild(
            std::make_unique<GameObject>("Player")
    );

    GameObject &weapon = player.AddChild(
            std::make_unique<GameObject>("Weapon")
    );

    EXPECT_EQ(root.ChildCount(), 1);
    EXPECT_EQ(player.ChildCount(), 1);

    EXPECT_EQ(player.Parent(), &root);
    EXPECT_EQ(weapon.Parent(), &player);

    EXPECT_EQ(root.ChildAt(0).ChildAt(0).Name(), "Weapon");
}

TEST(ObjectOwnershipTest, RejectsNullChild) {
    GameObject root{"Root"};

    EXPECT_THROW(root.AddChild(nullptr), std::invalid_argument);

    EXPECT_EQ(root.ChildCount(), 0);
}

TEST(ObjectOwnershipTest, SupportsConstTraversal) {
    GameObject root{"Root"};

    root.AddChild(std::make_unique<GameObject>("Player"));

    const GameObject &const_root = root;
    const GameObject &child = const_root.ChildAt(0);

    EXPECT_EQ(child.Name(), "Player");
    EXPECT_EQ(child.Parent(), &root);
}