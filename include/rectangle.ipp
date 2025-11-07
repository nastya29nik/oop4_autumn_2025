#pragma once

#include <algorithm>
#include <typeinfo>


namespace figure {

template <Scalar T>
bool Rectangle<T>::Validate(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
    Point<T> mid13 = {(p1.x + p3.x) / 2, (p1.y + p3.y) / 2};
    Point<T> mid24 = {(p2.x + p4.x) / 2, (p2.y + p4.y) / 2};
    if (DistSq(mid13, mid24) > Figure<T>::EPS) {
        return false;
    }
    
    double dot_product = (p2.x - p1.x) * (p4.x - p1.x) + (p2.y - p1.y) * (p4.y - p1.y);
    return std::abs(dot_product) < Figure<T>::EPS;
}

template <Scalar T>
Rectangle<T>::Rectangle(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4) {
    if (!Validate(p1, p2, p3, p4)) {
        throw exept::GeomFigueExcept("Error: Invalid points for Rectangle.");
    }
    _vert.Reserve(VERTEX_COUNT);
    _vert.PushBack(std::make_unique<Point<T>>(p1));
    _vert.PushBack(std::make_unique<Point<T>>(p2));
    _vert.PushBack(std::make_unique<Point<T>>(p3));
    _vert.PushBack(std::make_unique<Point<T>>(p4));
}

template<Scalar T>
Rectangle<T>::Rectangle(const Rectangle& other) {
    _vert.Reserve(other._vert.Size());
    for(size_t i = 0; i < other._vert.Size(); ++i) {
        _vert.PushBack(std::make_unique<Point<T>>(*other._vert[i]));
    }
}

template<Scalar T>
Rectangle<T>& Rectangle<T>::operator=(const Rectangle& other) {
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
Point<T> Rectangle<T>::Center() const {
    return {
        (_vert[0]->x + _vert[2]->x) / 2,
        (_vert[0]->y + _vert[2]->y) / 2
    };
}

template <Scalar T>
double Rectangle<T>::Area() const {
    double side1_sq = DistSq(*_vert[0], *_vert[1]);
    double side2_sq = DistSq(*_vert[0], *_vert[3]);
    return std::sqrt(side1_sq * side2_sq);
}

template <Scalar T>
void Rectangle<T>::Print(std::ostream& os) const {
    os << "Rectangle: " << *_vert[0] << ", " << *_vert[1] << ", " 
       << *_vert[2] << ", " << *_vert[3];
}

template <Scalar T>
void Rectangle<T>::Read(std::istream& is) {
    Point<T> p1, p2, p3, p4;
    std::cout << "Enter 4 vertices for Rectangle (x1 y1 x2 y2 x3 y3 x4 y4): ";
    is >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;
    *this = Rectangle<T>(p1, p2, p3, p4);
}

template <Scalar T>
bool Rectangle<T>::Equals(const Figure<T>& other) const {
    const auto* other_rect = dynamic_cast<const Rectangle<T>*>(&other);
    if (!other_rect) {
        return false;
    }
    double this_side1_sq = DistSq(*_vert[0], *_vert[1]);
    double this_side2_sq = DistSq(*_vert[0], *_vert[3]);
    double other_side1_sq = DistSq(*other_rect->_vert[0], *other_rect->_vert[1]);
    double other_side2_sq = DistSq(*other_rect->_vert[0], *other_rect->_vert[3]);
    if (this_side1_sq > this_side2_sq) {
        std::swap(this_side1_sq, this_side2_sq);
    }
    if (other_side1_sq > other_side2_sq) {
        std::swap(other_side1_sq, other_side2_sq);
    }
    return std::abs(this_side1_sq - other_side1_sq) < this->EPS &&
           std::abs(this_side2_sq - other_side2_sq) < this->EPS;
}

} // namespace figure