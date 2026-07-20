//
// Created by marks on 20.07.2026.
//

#ifndef PRODUCTIONCPPROADMAP_GAMEOBJECT_H
#define PRODUCTIONCPPROADMAP_GAMEOBJECT_H

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace production_cpp::object_ownership {
    class GameObject final {
    public:
        explicit GameObject(std::string name);

        GameObject(const GameObject &) = delete;

        GameObject &operator=(const GameObject &) = delete;

        GameObject(GameObject &&) = delete;

        GameObject &operator=(GameObject &&) = delete;

        virtual ~GameObject() = default;

        GameObject &AddChild(std::unique_ptr<GameObject> child);

        [[nodiscard]] const std::string &Name() const noexcept;

        [[nodiscard]] GameObject *Parent() noexcept;

        [[nodiscard]] const GameObject *Parent() const noexcept;

        [[nodiscard]] std::size_t ChildCount() const noexcept;

        GameObject &ChildAt(std::size_t index);

        [[nodiscard]] const GameObject &ChildAt(std::size_t index) const;

    private:
        std::string name_;

        // Non-owning pointer.
        GameObject *parent_{nullptr};

        // Sole Ownership of Subsidiary Facilities.
        std::vector<std::unique_ptr<GameObject>> children_;
    };
}

#endif //PRODUCTIONCPPROADMAP_GAMEOBJECT_H
