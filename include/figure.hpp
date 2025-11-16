#pragma once

#include <cmath>
#include <iostream>

#include "concepts.hpp"

namespace figure {

template <Scalar T>
struct Point {
    T x = 0;
    T y = 0;
};

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p);

template <Scalar T>
double DistSq(const Point<T>& p1, const Point<T>& p2);

template <Scalar T>
class Figure {
public:
    static constexpr double EPS = 1e-9;

    virtual ~Figure() = default;

    virtual Point<T> Center() const = 0;

    virtual void Print(std::ostream& os) const = 0;

    virtual double Area() const = 0;

    virtual void Read(std::istream& is) = 0;

    virtual bool Equals(const Figure<T>& other) const = 0;

    explicit operator double() const;
};

template <Scalar T>
bool operator==(const Figure<T>& l, const Figure<T>& r);

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& f);

template <Scalar T>
std::istream& operator>>(std::istream& is, Figure<T>& f);

} // namespace figure

#include "figure.ipp"