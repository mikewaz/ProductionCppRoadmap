///
/// Created by marks on 16.07.2026.
/// Rule of Five: если класс напрямую управляет ресурсом и требует собственного деструктора,
/// вероятно, ему необходимо осознанно определить остальные операции копирования и перемещения.
///

#include <cstddef>
#include <utility>
#include <algorithm>
#include "ManualIntArray.h"


ManualIntArray::ManualIntArray(std::size_t size)
        : data_(size > 0 ? new int[size]{} : nullptr),
          size_(size)
{
}

/// Copy constructor
ManualIntArray::ManualIntArray(const ManualIntArray& other)
        : data_(other.size_ > 0 ? new int[other.size_] : nullptr),
          size_(other.size_)
{
    if (size_ > 0)
        std::copy_n(other.data_, size_, data_);

}

/// Move constructor
ManualIntArray::ManualIntArray(ManualIntArray&& other) noexcept
        : data_(std::exchange(other.data_, nullptr)),
          size_(std::exchange(other.size_, 0))
{

}


ManualIntArray::~ManualIntArray() noexcept {
    delete[] data_;
}

[[nodiscard]] std::size_t ManualIntArray::Size() const noexcept { return size_; }

int* ManualIntArray::Data() noexcept { return data_; }

[[nodiscard]] const int* ManualIntArray::Data() const noexcept { return data_; }


ManualIntArray& ManualIntArray::operator=(const ManualIntArray& other) {
    if (this == &other)
        return *this;

    int *new_data =
            other.size_ > 0
            ? new int[other.size_]
            : nullptr;

    if (other.size_ > 0) {
        std::copy_n(
                other.data_,
                other.size_,
                new_data
        );
    }

    delete[] data_;

    data_ = new_data;
    size_ = other.size_;

    return *this;
}

ManualIntArray& ManualIntArray::operator=(ManualIntArray&& other) noexcept {
    if (this == &other)
        return *this;

    delete[] data_;

    data_ = std::exchange(other.data_, nullptr);
    size_ = std::exchange(other.size_, 0);

    return *this;
}

int& ManualIntArray::operator[](std::size_t index) noexcept {
    return data_[index];
}

const int& ManualIntArray::operator[](std::size_t index) const noexcept {
    return data_[index];
}