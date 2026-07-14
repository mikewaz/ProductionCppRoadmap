//
// Created by marks on 13.07.2026.
//

#ifndef PRODUCTIONCPPROADMAP_TRACKEDOBJECT_H
#define PRODUCTIONCPPROADMAP_TRACKEDOBJECT_H
#include <cstdint>
#include <string>

struct TrackedObjectStats
{
    std::size_t direct_constructions{};
    std::size_t copy_constructions{};
    std::size_t move_constructions{};

    std::size_t copy_assignments{};
    std::size_t move_assignments{};

    std::size_t destructions{};
    std::size_t alive{};
};

class TrackedObject {
public:
    explicit TrackedObject(std::string name);                   // явный конструктор

    TrackedObject(const TrackedObject& other);                  // copy constructor
    TrackedObject(TrackedObject&& other) noexcept;              // move constructor (noexcept - обещает, что конструктор не выбросит исключение)
                                                                // TrackedObject&& other - Rvalue

    TrackedObject& operator=(const TrackedObject& other);       // copy assignment
    TrackedObject& operator=(TrackedObject&& other) noexcept;   // move assignment (noexcept - обещает, что конструктор не выбросит исключение)
                                                                // TrackedObject&& other - Rvalue

    ~TrackedObject();                                           // деструктор

    [[nodiscard]] std::uint64_t Id() const noexcept;
    [[nodiscard]] const std::string& Name() const noexcept;

    [[nodiscard]] static TrackedObjectStats Stats() noexcept;
    static void ResetStats() noexcept;

private:
    static void Log(
        const char* operation,
        const TrackedObject& object,
        const TrackedObject* source = nullptr
    ) noexcept;

    static TrackedObjectStats stats_;
    static std::uint64_t next_id_;

    std::uint64_t id_{};
    std::string name_;
};


#endif //PRODUCTIONCPPROADMAP_TRACKEDOBJECT_H