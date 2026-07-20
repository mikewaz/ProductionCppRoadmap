//
// Created by marks on 20.07.2026.
//

#ifndef PRODUCTIONCPPROADMAP_INTARRAY_H
#define PRODUCTIONCPPROADMAP_INTARRAY_H


#include <vector>

namespace production_cpp::rule_of_zero_or_rule_of_five {
    class IntArray final {
    public:
        explicit IntArray(std::size_t size);

        [[nodiscard]] std::size_t Size() const noexcept;

        int &operator[](std::size_t index);

        const int &operator[](std::size_t index) const;

    private:
        std::vector<int> data_;
    };
}


#endif //PRODUCTIONCPPROADMAP_INTARRAY_H
