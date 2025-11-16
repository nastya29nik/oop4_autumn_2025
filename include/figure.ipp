#pragma once

namespace figure {

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

template <Scalar T>
double DistSq(const Point<T>& p1, const Point<T>& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

template <Scalar T>
Figure<T>::operator double() const {
    return Area();
}

template <Scalar T>
bool operator==(const Figure<T>& l, const Figure<T>& r) {
    return l.Equals(r);
}

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& f) {
    f.Print(os);
    return os;
}

template <Scalar T>
std::istream& operator>>(std::istream& is, Figure<T>& f) {
    f.Read(is);
    return is;
}

} // namespace figure