//
// Created by marks on 20.07.2026.
//

#include <cstddef>
#include "IntArray.h"

namespace production_cpp::rule_of_zero_or_rule_of_five {
    IntArray::IntArray(std::size_t size)
        : data_(size) {
    }


    std::size_t IntArray::Size() const noexcept{
        return data_.size();
    }


    int &IntArray::operator[](std::size_t index) {
        return data_.at(index);
    }

    const int &IntArray::operator[](std::size_t index) const {
        return data_.at(index);
    }
}