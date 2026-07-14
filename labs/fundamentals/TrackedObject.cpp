//
// Created by marks on 13.07.2026.
//

#include "TrackedObject.h"

#include <cassert>

static_assert(std::is_nothrow_move_constructible_v<std::string>);
static_assert(std::is_nothrow_move_assignable_v<std::string>);

TrackedObjectStats TrackedObject::stats_{};
std::uint64_t TrackedObject::next_id_{1};

TrackedObject::TrackedObject(std::string name)
    : id_(next_id_++),
      name_(std::move(name))
{
    ++stats_.direct_constructions;
    ++stats_.alive;

    Log("construct", *this);
}

TrackedObject::TrackedObject(const TrackedObject& other)
    : id_(next_id_++),
      name_(other.name_)
{
    ++stats_.copy_constructions;
    ++stats_.alive;

    Log("copy construct", *this, &other);
}

TrackedObject::TrackedObject(TrackedObject&& other) noexcept
    : id_(next_id_++),
      name_(std::move(other.name_))
{
    other.name_.clear();

    ++stats_.move_constructions;
    ++stats_.alive;

    Log("move construct", *this, &other);
}

TrackedObject& TrackedObject::operator=(const TrackedObject& other) {
    ++stats_.copy_assignments;

    if (this != &other) {
        name_ = other.name_;
    }

    Log("copy assign", *this, &other);

    return *this;
}

TrackedObject& TrackedObject::operator=(TrackedObject&& other) noexcept {
    ++stats_.move_assignments;

    if (this != &other) {
        name_ = std::move(other.name_);
        other.name_.clear();
    }

    Log("move assign", *this, &other);

    return *this;
}

TrackedObject::~TrackedObject() {
    Log("destroy", *this);

    assert(stats_.alive > 0);

    ++stats_.destructions;
    --stats_.alive;
}

std::uint64_t TrackedObject::Id() const noexcept {
    return id_;
}

const std::string& TrackedObject::Name() const noexcept {
    return name_;
}

TrackedObjectStats TrackedObject::Stats() noexcept {
    return stats_;
}

void TrackedObject::ResetStats() noexcept {
    // Reset допустим только тогда, когда все предыдущие объекты уничтожены.
    assert(stats_.alive == 0);

    stats_ = {};
    next_id_ = 1;
}

void TrackedObject::Log(
    const char* operation,
    const TrackedObject& object,
    const TrackedObject* source
) noexcept
{
    if (source == nullptr)
    {
        std::fprintf(
            stderr,
            "%-16s object=%llu name=\"%s\"\n",
            operation,
            static_cast<unsigned long long>(object.id_),
            object.name_.c_str()
        );

        return;
    }

    std::fprintf(
        stderr,
        "%-16s object=%llu source=%llu name=\"%s\"\n",
        operation,
        static_cast<unsigned long long>(object.id_),
        static_cast<unsigned long long>(source->id_),
        object.name_.c_str()
    );
}
