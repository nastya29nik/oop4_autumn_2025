#include <stdexcept>
#include <utility>

namespace vector {

template <class T>
Vector<T>::Vector() : _arr(nullptr), _sz(0), _cap(0) {}

template <class T>
Vector<T>::Vector(Vector&& other) noexcept : _arr(nullptr), _sz(0), _cap(0) {
    std::swap(_arr, other._arr);
    std::swap(_sz, other._sz);
    std::swap(_cap, other._cap);
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        Clear();
        _arr = nullptr;
        _sz = 0;
        _cap = 0;
        std::swap(_arr, other._arr);
        std::swap(_sz, other._sz);
        std::swap(_cap, other._cap);
    }
    return *this;
}

template <class T>
T& Vector<T>::operator[](size_t pos) {
    if (pos >= _sz) {
        throw std::out_of_range("Error: Vector index out of range");
    }
    return _arr[pos];
}

template <class T>
const T& Vector<T>::operator[](size_t pos) const {
    if (pos >= _sz) {
        throw std::out_of_range("Error: Vector index out of range");
    }
    return _arr[pos];
}

template <class T>
void Vector<T>::PushBack(T&& value) {
    if (_sz == _cap) {
        size_t new_cap = (_cap == 0) ? 1 : _cap * 2;
        Reserve(new_cap);
    }
    _arr[_sz++] = std::move(value);
}

template <class T>
void Vector<T>::Erase(size_t ind) {
    if (ind >= _sz) {
        throw std::out_of_range("Error: Erase index out of range");
    }
    for (size_t i = ind; i < _sz - 1; ++i) {
        _arr[i] = std::move(_arr[i + 1]);
    }
    --_sz;
}

template <class T>
size_t Vector<T>::Size() const {
    return _sz;
}

template <class T>
bool Vector<T>::IsEmpty() const noexcept {
    return _sz == 0;
}

template <class T>
void Vector<T>::Clear() {
    _sz = 0;
}

template <class T>
void Vector<T>::Reserve(size_t new_cap) {
    if (new_cap <= _cap) {
        return;
    }
    std::shared_ptr<T[]> new_arr(new T[new_cap], std::default_delete<T[]>());
    for (size_t i = 0; i < _sz; ++i) {
        new_arr[i] = std::move(_arr[i]);
    }
    _arr = std::move(new_arr);
    _cap = new_cap;
}

} // namespace vector