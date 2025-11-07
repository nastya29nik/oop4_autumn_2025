#pragma once

#include <typeinfo>

namespace figure {

template <Scalar T>
bool Square<T>::Validate(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
    double d2 = DistSq(p1, p2);
    double d3 = DistSq(p1, p3);
    double d4 = DistSq(p1, p4);

    if (d2 < Figure<T>::EPS || d3 < Figure<T>::EPS || d4 < Figure<T>::EPS) return false;

    if (std::abs(d2 - d4) < Figure<T>::EPS && std::abs(2.0 * d2 - d3) < Figure<T>::EPS) {
        double d = DistSq(p2, p3);
        return std::abs(d - d4) < Figure<T>::EPS;
    }
    if (std::abs(d3 - d4) < Figure<T>::EPS && std::abs(2.0 * d3 - d2) < Figure<T>::EPS) {
        double d = DistSq(p3, p4);
        return std::abs(d - d2) < Figure<T>::EPS;
    }
    return false;
}

template <Scalar T>
Square<T>::Square(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4) {
    if (!Validate(p1, p2, p3, p4)) {
        throw exept::GeomFigueExcept("Invalid points for Square.");
    }
    _vert.Reserve(VERTEX_COUNT);
    _vert.PushBack(std::make_unique<Point<T>>(p1));
    _vert.PushBack(std::make_unique<Point<T>>(p2));
    _vert.PushBack(std::make_unique<Point<T>>(p3));
    _vert.PushBack(std::make_unique<Point<T>>(p4));
}

template<Scalar T>
Square<T>::Square(const Square& other) {
    _vert.Reserve(other._vert.Size());
    for(size_t i = 0; i < other._vert.Size(); ++i) {
        _vert.PushBack(std::make_unique<Point<T>>(*other._vert[i]));
    }
}

template<Scalar T>
Square<T>& Square<T>::operator=(const Square& other) {
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
Point<T> Square<T>::Center() const {
    return {
        (_vert[0]->x + _vert[2]->x) / 2,
        (_vert[0]->y + _vert[2]->y) / 2
    };
}

template <Scalar T>
double Square<T>::Area() const {
    return DistSq(*_vert[0], *_vert[1]);
}

template <Scalar T>
void Square<T>::Print(std::ostream& os) const {
    os << "Square: " << *_vert[0] << ", " << *_vert[1] << ", " 
       << *_vert[2] << ", " << *_vert[3];
}

template <Scalar T>
void Square<T>::Read(std::istream& is) {
    Point<T> p1, p2, p3, p4;
    std::cout << "Enter 4 vertices for Square (x1 y1 x2 y2 x3 y3 x4 y4): ";
    is >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;
    *this = Square<T>(p1, p2, p3, p4);
}

template <Scalar T>
bool Square<T>::Equals(const Figure<T>& other) const {
    const auto* other_square = dynamic_cast<const Square<T>*>(&other);
    if (!other_square) {
        return false;
    }
    double this_side_sq = DistSq(*_vert[0], *_vert[1]);
    double other_side_sq = DistSq(*other_square->_vert[0], *other_square->_vert[1]);
    return std::abs(this_side_sq - other_side_sq) < this->EPS;
}

} // namespace figure