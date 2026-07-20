//
// Created by marks on 20.07.2026.
//

#include <gtest/gtest.h>
#include "labs/fundamentals/object_ownership/GameObject.h"

namespace GameObject = production_cpp::object_ownership;

TEST(GameObject, ParentOwnsAddedChild) {
    GameObject::GameObject root{"root"};

    auto child = std::make_unique<GameObject::GameObject>("child");
    auto child_address = child.get();
    GameObject::GameObject &added_child = root.AddChild(std::move(child));

    EXPECT_EQ(child, nullptr);

    EXPECT_EQ(root.ChildCount(), 1);
    EXPECT_EQ(&added_child, child_address);

    EXPECT_EQ(added_child.Name(), "child");
    EXPECT_EQ(added_child.Parent(), &root);
}

TEST(ObjectOwnershipTest, BuildsObjectHierarchy) {
    GameObject::GameObject root{"Root"};

    GameObject::GameObject &player = root.AddChild(
            std::make_unique<GameObject::GameObject>("Player")
    );

    GameObject::GameObject &weapon = player.AddChild(
            std::make_unique<GameObject::GameObject>("Weapon")
    );

    EXPECT_EQ(root.ChildCount(), 1);
    EXPECT_EQ(player.ChildCount(), 1);

    EXPECT_EQ(player.Parent(), &root);
    EXPECT_EQ(weapon.Parent(), &player);

    EXPECT_EQ(root.ChildAt(0).ChildAt(0).Name(), "Weapon");
}

TEST(ObjectOwnershipTest, RejectsNullChild) {
    GameObject::GameObject root{"Root"};

    EXPECT_THROW(root.AddChild(nullptr), std::invalid_argument);

    EXPECT_EQ(root.ChildCount(), 0);
}

TEST(ObjectOwnershipTest, SupportsConstTraversal) {
    GameObject::GameObject root{"Root"};

    root.AddChild(std::make_unique<GameObject::GameObject>("Player"));

    const GameObject::GameObject &const_root = root;
    const GameObject::GameObject &child = const_root.ChildAt(0);

    EXPECT_EQ(child.Name(), "Player");
    EXPECT_EQ(child.Parent(), &root);
}