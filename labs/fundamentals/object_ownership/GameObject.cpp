//
// Created by marks on 20.07.2026.
//

#include <iostream>
#include "GameObject.h"

namespace production_cpp::object_ownership {
    GameObject::GameObject(std::string name)
        : name_(std::move(name))
    { }


    GameObject &GameObject::AddChild(std::unique_ptr<GameObject> child) {
        if (child == nullptr)
            throw std::invalid_argument("child is nullptr");

        auto c = child.get();
        child->parent_ = this;
        children_.push_back(std::move(child));

        return *c;
    }


    const std::string &GameObject::Name() const noexcept { return name_; }


    GameObject *GameObject::Parent() noexcept { return parent_; }

    const GameObject *GameObject::Parent() const noexcept { return parent_; }


    std::size_t GameObject::ChildCount() const noexcept { return children_.size(); }

    GameObject &GameObject::ChildAt(std::size_t index) { return *children_[index]; }

    const GameObject &GameObject::ChildAt(std::size_t index) const { return *children_[index]; }
}