#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "exception.hpp"
#include "figure.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "trapezoid.hpp"
#include "vector.hpp"

using namespace figure;
using namespace vector;

int main() {
    Vector<std::shared_ptr<Figure<double>>> figures;

    std::cout << "0 - Exit\n";
    std::cout << "1 - Add figure\n";
    std::cout << "2 - Show points of all\n";
    std::cout << "3 - Show center and area\n";
    std::cout << "4 - Total area\n";
    std::cout << "5 - Delete figure\n";
    
    int choice;

    while (true) {
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Error: Invalid input\n";
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        try {
            switch (choice) {
                case 1: {
                    std::cout << "Figures (s - square, r - rectangle, t - trapezoid): ";
                    char fig_type;
                    std::cin >> fig_type;
                    std::shared_ptr<Figure<double>> new_figure = nullptr;

                    if (fig_type == 's') {
                        new_figure = std::make_shared<Square<double>>();
                    } else if (fig_type == 'r') {
                        new_figure = std::make_shared<Rectangle<double>>();
                    } else if (fig_type == 't') {
                        new_figure = std::make_shared<Trapezoid<double>>();
                    } else {
                        std::cout << "Unknown type.\n";
                        continue;
                    }
                    std::cin >> *new_figure;
                    figures.PushBack(std::move(new_figure));
                    std::cout << "Figure is added.\n";
                    break;
                }
                case 2: {
                    if (figures.IsEmpty()) {
                        std::cout << "Empty\n";
                    } else {
                        for (size_t i = 0; i < figures.Size(); ++i) {
                            std::cout << i << ": " << *figures[i] << std::endl;
                        }
                    }
                    break;
                }
                case 3: {
                     if (figures.IsEmpty()) {
                        std::cout << "Empty\n";
                    } else {
                        for (size_t i = 0; i < figures.Size(); ++i) {
                            std::cout << i << ": " << *figures[i]
                                      << " | Centre: " << figures[i]->Center()
                                      << " | Area: " << static_cast<double>(*figures[i]) << std::endl;
                        }
                    }
                    break;
                }
                case 4: {
                    double total_area = 0.0;
                    for (size_t i = 0; i < figures.Size(); ++i) {
                        total_area += static_cast<double>(*figures[i]);
                    }
                    std::cout << "Total area: " << total_area << std::endl;
                    break;
                }
                case 5: {
                    if (figures.IsEmpty()) {
                        std::cout << "Empty\n";
                        break;
                    }
                    std::cout << "Input index (from 0 to " << figures.Size() - 1 << "): ";
                    size_t index;
                    std::cin >> index;

                    if (std::cin.fail()) {
                         std::cout << "Error: incorrect index\n";
                         std::cin.clear();
                         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                         break;
                    }
                    figures.Erase(index);
                    std::cout << "Figure with index " << index << " is deleted.\n";
                    break;
                }
                case 0: {
                    return 0;
                }
                default: {
                    std::cout << "Unknown command\n";
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
             if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    return 0;
}