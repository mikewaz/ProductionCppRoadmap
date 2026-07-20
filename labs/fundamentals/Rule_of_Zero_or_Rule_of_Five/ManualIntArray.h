//
// Created by marks on 16.07.2026.
//

#ifndef PRODUCTIONCPPROADMAP_MANUALINTARRAY_H
#define PRODUCTIONCPPROADMAP_MANUALINTARRAY_H

#include <cstddef>

class ManualIntArray {
public:
    ManualIntArray(std::size_t size);
    ManualIntArray(const ManualIntArray& other);
    ManualIntArray(ManualIntArray&& other) noexcept;

    ~ManualIntArray() noexcept;

    ManualIntArray& operator=(const ManualIntArray& other);
    ManualIntArray& operator=(ManualIntArray&& other) noexcept;

    [[nodiscard]] std::size_t Size() const noexcept;

    int* Data() noexcept;
    [[nodiscard]] const int* Data() const noexcept;

    int& operator[](std::size_t index) noexcept;
    const int& operator[](std::size_t index) const noexcept;

private:
    int* data_{nullptr};
    std::size_t size_{};
};


#endif //PRODUCTIONCPPROADMAP_MANUALINTARRAY_H
