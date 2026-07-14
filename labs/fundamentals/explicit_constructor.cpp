#include "explicit_constructor.h"


explicit_constructor::explicit_constructor(int id)
    : id_(id)
{
}

int explicit_constructor::getId() const noexcept {
    return id_;
}


implicit_constructor::implicit_constructor(int id)
    : id_(id)
{
}

[[nodiscard]] int implicit_constructor::getId() const noexcept {
    return id_;
}