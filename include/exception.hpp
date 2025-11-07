#pragma once

#include <stdexcept>
#include <string>

namespace exept {

class GeomFigueExcept : public std::runtime_error {
public:
    explicit GeomFigueExcept(const std::string& message)
        : std::runtime_error(message) {}
};

} // namespace exept