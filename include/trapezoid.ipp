#pragma once

#include <typeinfo>

namespace figure {

template <Scalar T>
bool Trapezoid<T>::Validate(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
    return std::abs(DistSq(p1, p3) - DistSq(p2, p4)) < Figure<T>::EPS;
}

template <Scalar T>
Trapezoid<T>::Trapezoid(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4) {
    if (!Validate(p1, p2, p3, p4)) {
        throw exept::GeomFigueExcept("Error: Invalid points for Trapezoid.");
    }
    _vert.Reserve(VERTEX_COUNT);
    _vert.PushBack(std::make_unique<Point<T>>(p1));
    _vert.PushBack(std::make_unique<Point<T>>(p2));
    _vert.PushBack(std::make_unique<Point<T>>(p3));
    _vert.PushBack(std::make_unique<Point<T>>(p4));
}

template<Scalar T>
Trapezoid<T>::Trapezoid(const Trapezoid& other) {
    _vert.Reserve(other._vert.Size());
    for(size_t i = 0; i < other._vert.Size(); ++i) {
        _vert.PushBack(std::make_unique<Point<T>>(*other._vert[i]));
    }
}

template<Scalar T>
Trapezoid<T>& Trapezoid<T>::operator=(const Trapezoid& other) {
    if (this != &other) {
        _vert.Clear();
        _vert.Reserve(other._vert.Size());
        for(size_t i = 0; i < other._vert.Size(); ++i) {
            _vert.PushBack(std::make_unique<Point<T>>(*other._vert[i]));
        }
    }
    return *this;
}

template <Scalar T>
Point<T> Trapezoid<T>::Center() const {
    return {
        (_vert[0]->x + _vert[1]->x + _vert[2]->x + _vert[3]->x) / 4,
        (_vert[0]->y + _vert[1]->y + _vert[2]->y + _vert[3]->y) / 4
    };
}

template <Scalar T>
double Trapezoid<T>::Area() const {
    double area = 0.5 * std::abs(
        _vert[0]->x * _vert[1]->y - _vert[1]->x * _vert[0]->y +
        _vert[1]->x * _vert[2]->y - _vert[2]->x * _vert[1]->y +
        _vert[2]->x * _vert[3]->y - _vert[3]->x * _vert[2]->y +
        _vert[3]->x * _vert[0]->y - _vert[0]->x * _vert[3]->y
    );
    return area;
}

template <Scalar T>
void Trapezoid<T>::Print(std::ostream& os) const {
    os << "Trapezoid: " << *_vert[0] << ", " << *_vert[1] << ", " 
       << *_vert[2] << ", " << *_vert[3];
}

template <Scalar T>
void Trapezoid<T>::Read(std::istream& is) {
    Point<T> p1, p2, p3, p4;
    std::cout << "Enter 4 vertices for Trapezoid (x1 y1 x2 y2 x3 y3 x4 y4): ";
    is >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;
    *this = Trapezoid<T>(p1, p2, p3, p4);
}

template <Scalar T>
bool Trapezoid<T>::Equals(const Figure<T>& other) const {
    const auto* other_trap = dynamic_cast<const Trapezoid<T>*>(&other);
    if (!other_trap) {
        return false;
    }
    vector::Vector<double> this_sides_sq;
    this_sides_sq.Reserve(VERTEX_COUNT);
    this_sides_sq.PushBack(DistSq(*_vert[0], *_vert[1]));
    this_sides_sq.PushBack(DistSq(*_vert[1], *_vert[2]));
    this_sides_sq.PushBack(DistSq(*_vert[2], *_vert[3]));
    this_sides_sq.PushBack(DistSq(*_vert[3], *_vert[0]));
    vector::Vector<double> other_sides_sq;
    other_sides_sq.Reserve(VERTEX_COUNT);
    other_sides_sq.PushBack(DistSq(*other_trap->_vert[0], *other_trap->_vert[1]));
    other_sides_sq.PushBack(DistSq(*other_trap->_vert[1], *other_trap->_vert[2]));
    other_sides_sq.PushBack(DistSq(*other_trap->_vert[2], *other_trap->_vert[3]));
    other_sides_sq.PushBack(DistSq(*other_trap->_vert[3], *other_trap->_vert[0]));
    auto vec_sort = [](vector::Vector<double>& vec) {
        if (vec.IsEmpty()) {
            return;
        }
        size_t n = vec.Size();
        for (size_t i = 0; i < n - 1; ++i) {
            for (size_t j = 0; j < n - i - 1; ++j) {
                if (vec[j] > vec[j + 1]) {
                    std::swap(vec[j], vec[j + 1]);
                }
            }
        }
    };
    vec_sort(this_sides_sq);
    vec_sort(other_sides_sq);
    for (size_t i = 0; i < this_sides_sq.Size(); ++i) {
        if (std::abs(this_sides_sq[i] - other_sides_sq[i]) >= this->EPS) {
            return false;
        }
    }
    return true;
}

} // namespace figure