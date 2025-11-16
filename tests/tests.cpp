#include "gtest/gtest.h"

#include "exception.hpp"
#include "figure.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "trapezoid.hpp"
#include "vector.hpp"

using namespace figure;
using namespace vector;
using namespace exept;

TEST(FigureCreationTest, ValidFigures) {
    Square<double> s({0,0}, {2,0}, {2,2}, {0,2});
    ASSERT_NEAR(s.Area(), 4.0, Figure<double>::EPS);
    Point<double> s_center = s.Center();
    ASSERT_NEAR(s_center.x, 1.0, Figure<double>::EPS);
    ASSERT_NEAR(s_center.y, 1.0, Figure<double>::EPS);

    Rectangle<double> r({0,0}, {3,0}, {3,5}, {0,5});
    ASSERT_NEAR(r.Area(), 15.0, Figure<double>::EPS);
}

TEST(FigureCreationTest, InvalidFiguresThrowException) {
    EXPECT_THROW(Square<double> s({0,0}, {3,0}, {3,2}, {0,2}), GeomFigueExcept);
    EXPECT_THROW(Rectangle<double> r({0,0}, {1,1}, {2,1}, {1,0}), GeomFigueExcept);
}

TEST(PolymorphismTest, TotalAreaCalculation) {
    Vector<std::shared_ptr<Figure<double>>> figures;

    figures.PushBack(std::make_shared<Square<double>>(Point<double>{0,0}, Point<double>{2,0}, Point<double>{2,2}, Point<double>{0,2}));
    figures.PushBack(std::make_shared<Rectangle<double>>(Point<double>{0,0}, Point<double>{5,0}, Point<double>{5,3}, Point<double>{0,3}));
    figures.PushBack(std::make_shared<Trapezoid<double>>(Point<double>{0,4}, Point<double>{2,4}, Point<double>{3,0}, Point<double>{-1,0}));

    double total_area = 0.0;
    for (size_t i = 0; i < figures.Size(); ++i) {
        total_area += static_cast<double>(*figures[i]);
    }

    ASSERT_NEAR(total_area, 31.0, Figure<double>::EPS);
}

TEST(VectorCompleteTest, MoveAndExceptions) {
    Vector<int> v1;
    v1.PushBack(10);
    v1.PushBack(20);

    Vector<int> v2 = std::move(v1);
    ASSERT_EQ(v1.Size(), 0);
    ASSERT_EQ(v2.Size(), 2);
    ASSERT_EQ(v2[0], 10);

    Vector<int> v3;
    v3 = std::move(v2);
    ASSERT_EQ(v2.Size(), 0);
    ASSERT_EQ(v3.Size(), 2);
    ASSERT_EQ(v3[1], 20);

    EXPECT_THROW(v3[5], std::out_of_range);
    EXPECT_THROW(v3.Erase(5), std::out_of_range);
}

TEST(FigureLogicTest, GeometricEqualityAndAssignment) {
    Square<int> s1({0,0}, {1,0}, {1,1}, {0,1});
    Square<int> s2({5,5}, {6,5}, {6,6}, {5,6});
    EXPECT_TRUE(s1.Equals(s2));

    Rectangle<int> r1({0,0}, {3,0}, {3,2}, {0,2});
    Rectangle<int> r2({0,0}, {3,0}, {3,2}, {0,2});

    r2 = r1;
    EXPECT_TRUE(r2.Equals(r1));
}

TEST(OutputStreamTest, PrintFunction) {
    Square<int> s({0,0}, {1,0}, {1,1}, {0,1});
    
    std::stringstream ss;
    s.Print(ss);
    
    std::string expected_output = "Square: (0, 0), (1, 0), (1, 1), (0, 1)";
    ASSERT_EQ(ss.str(), expected_output);
}

TEST(FigureLogicTest, Inequality) {
    Rectangle<double> r({0,0}, {2,0}, {2,2}, {0,2});
    Square<double> s({0,0}, {2,0}, {2,2}, {0,2});
    EXPECT_FALSE(r.Equals(s));
    EXPECT_FALSE(s.Equals(r));

    Rectangle<double> r1({0,0}, {2,0}, {2,6}, {0,6});
    Rectangle<double> r2({0,0}, {3,0}, {3,4}, {0,4});
    EXPECT_FALSE(r1.Equals(r2));
}

TEST(FigureLogicTest, CopyAndSelfAssignment) {
    Rectangle<int> r1({0,0}, {3,0}, {3,2}, {0,2});
    
    Rectangle<int> r2(r1);
    EXPECT_TRUE(r2.Equals(r1));

    r1 = r1; 
    Rectangle<int> r_expected({0,0}, {3,0}, {3,2}, {0,2});
    EXPECT_TRUE(r1.Equals(r_expected));
}

TEST(FigureCreationTest, ValidTrapezoid) {
    Trapezoid<double> t({0,4}, {2,4}, {3,0}, {-1,0});
    
    ASSERT_NEAR(t.Area(), 12.0, Figure<double>::EPS);
    
    Point<double> t_center = t.Center();
    ASSERT_NEAR(t_center.x, 1.0, Figure<double>::EPS);
    ASSERT_NEAR(t_center.y, 2.0, Figure<double>::EPS);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}