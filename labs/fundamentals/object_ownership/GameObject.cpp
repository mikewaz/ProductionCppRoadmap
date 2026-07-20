//
// Created by marks on 20.07.2026.
//

#include <stdexcept>
#include <utility>
#include "GameObject.h"

namespace production_cpp::object_ownership {
    GameObject::GameObject(std::string name)
            : name_(std::move(name)) {}


    GameObject &GameObject::AddChild(std::unique_ptr<GameObject> child) {
        if (child == nullptr)
            throw std::invalid_argument{"Child cannot be null"};

        children_.push_back(std::move(child));

        GameObject &added_child = *children_.back();
        added_child.parent_ = this;

        return added_child;
    }


    const std::string &GameObject::Name() const noexcept { return name_; }


    GameObject *GameObject::Parent() noexcept { return parent_; }

    const GameObject *GameObject::Parent() const noexcept { return parent_; }


    std::size_t GameObject::ChildCount() const noexcept { return children_.size(); }

    GameObject &GameObject::ChildAt(std::size_t index) { return *children_.at(index); }

    const GameObject &GameObject::ChildAt(std::size_t index) const { return *children_.at(index); }
}