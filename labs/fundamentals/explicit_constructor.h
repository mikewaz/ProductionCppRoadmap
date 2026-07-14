#ifndef PRODUCTIONCPPROADMAP_EXPLICIT_CONSTRUCTOR_H
#define PRODUCTIONCPPROADMAP_EXPLICIT_CONSTRUCTOR_H

class explicit_constructor
{
public:
    explicit explicit_constructor(int id);

    [[nodiscard]] int getId() const noexcept;

private:
    int id_;
};

class implicit_constructor
{
public:
    implicit_constructor(int id);

    [[nodiscard]] int getId() const noexcept;

private:
    int id_;
};

#endif //PRODUCTIONCPPROADMAP_EXPLICIT_CONSTRUCTOR_H
