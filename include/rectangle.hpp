#pragma once

#include <memory>

#include "exception.hpp"
#include "figure.hpp"
#include "vector.hpp"

namespace figure {

template <Scalar T>
class Rectangle : public Figure<T> {
public:
    static constexpr size_t VERTEX_COUNT = 4;

    Rectangle() = default;

    Rectangle(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);

    Rectangle(const Rectangle& other);

    Rectangle& operator=(const Rectangle& other);

    Point<T> Center() const override;

    void Print(std::ostream& os) const override;

    double Area() const override;

    void Read(std::istream& is) override;

    bool Equals(const Figure<T>& other) const override;

private:
    static bool Validate(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4);

    vector::Vector<std::unique_ptr<Point<T>>> _vert;
};

} // namespace figure

#include "rectangle.ipp"