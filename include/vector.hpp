#pragma once

#include <memory>
#include <cstddef>

namespace vector {

template <class T>
class Vector {
public:
    Vector();

    ~Vector() = default;

    Vector(const Vector&) = delete;

    Vector& operator=(const Vector&) = delete;

    Vector(Vector&&) noexcept;

    Vector& operator=(Vector&&) noexcept;

    T& operator[](size_t pos);

    const T& operator[](size_t pos) const;

    void PushBack(T&& value);

    void Erase(size_t ind);

    size_t Size() const;

    bool IsEmpty() const noexcept;

    void Clear();

    void Reserve(size_t new_cap);

private:
    std::shared_ptr<T[]> _arr;
    size_t _sz;
    size_t _cap;
};

} // namespace vector

#include "vector.ipp"