#include <typeinfo>

#include "./curve.h"
#include "./simplification.h"

Curve::Curve(const Points &points, const std::string &name) : Points(points), vstart{0}, vend{points.size() - 1}, name{name} {
    if (points.empty()) { 
        std::cerr << "warning: constructed empty curve" << std::endl;
        return; 
    }
    #if DEBUG
    std::cout << "constructed curve of complexity " << points.size() << std::endl;
    #endif
}

Curves Curves::simplify(const curve_size_t l, const bool approx = false) {
    Curves result(size(), l, Curves::dimensions());
    for (curve_number_t i = 0; i < size(); ++i) {
        if (approx) {
            Curve simplified_curve = Simplification::approximate_minimum_error_simplification(std::vector<Curve>::operator[](i), l);
            simplified_curve.set_name("Simplification of " + std::vector<Curve>::operator[](i).get_name());
            result[i] = simplified_curve;
        } else {
            Simplification::Subcurve_Shortcut_Graph graph(std::vector<Curve>::operator[](i));
            Curve simplified_curve = graph.minimum_error_simplification(l);
            simplified_curve.set_name("Simplification of " + std::vector<Curve>::operator[](i).get_name());
            result[i] = simplified_curve;
        }
        #if DEBUG
        std::cout << "Simplified curve " << i + 1 << "/" << size() << "." << std::endl;
        #endif
    }
    return result;
}

std::string Curve::repr() const {
    std::stringstream ss;
    ss << "fred.Curve '" << name << "' of complexity " << complexity() << " and " << dimensions() << " dimensions";
    return ss.str();
}

std::string Curves::repr() const {
    std::stringstream ss;
    ss << "fred.Curves collection with " << number() << " curves";
    return ss.str();
}

std::string Curve::str() const {
    std::stringstream ss;
    ss << name << std::endl;
    ss << *this;
    return ss.str();
}

std::string Curves::str() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

std::string Curve::get_name() const {
    return name;
}

void Curve::set_name(const std::string &name) {
    this->name = name;
}

std::ostream& operator<<(std::ostream &out, const Curve &curve) {
    if (curve.empty()) return out;
    out << "[";
    
    for (curve_size_t i = 0; i < curve.complexity() - 1; ++i) {
        out << curve[i] << ", ";
    }
    
    out << curve[curve.complexity() -1] << "]";

    return out;
}

std::ostream& operator<<(std::ostream &out, const Curves &curves) {
    if (curves.empty()) return out;
    out << "{";
    
    for (curve_number_t i = 0; i < curves.number() - 1; ++i) {
        out << curves[i] << ", ";
    }
    
    out << curves[curves.size() -1] << "}";

    return out;
}