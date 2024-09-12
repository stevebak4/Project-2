#include "point.h"

std::string Point::str() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

std::string Point::repr() const {
    std::stringstream ss;
    ss << "fred.Point of " << dimensions() << " dimensions";
    return ss.str();
}

std::string Points::str() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

std::string Points::repr() const {
    std::stringstream ss;
    ss << size() << " fred.Points of " << dimensions() << " dimensions";
    return ss.str();
}

std::ostream& operator<<(std::ostream &out, const Point &p) {
    if (p.empty()) return out;
    out << "(";
    
    for (dimensions_t i = 0; i < p.dimensions() - 1; ++i){
        out << p[i] << ",";
    }
    
    out << p[p.dimensions() - 1] << ")";

    return out;
}

std::ostream& operator<<(std::ostream &out, const Points &p) {
    if (p.empty()) return out;
    out << "{";
    
    for (curve_size_t i = 0; i < p.size() - 1; ++i){
        out << p[i] << ",";
    }
    
    out << p[p.size() - 1] << "}";

    return out;
}