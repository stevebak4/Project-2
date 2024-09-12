#ifndef TYPES_H_H
#define TYPES_H_H


#pragma once

#include <vector>
#include <cmath>
#include <limits>

typedef double distance_t; // Distances
typedef double coordinate_t; // Coordinates
typedef long double parameter_t; // Parameters, i.e., values in [0,1]

typedef unsigned long dimensions_t; // Dimensions
typedef unsigned long curve_size_t; // Curve complexities
typedef unsigned long curve_number_t; // Number of curves

class Point;
class Curve;
class Interval;

using Vector = Point;
using Intervals = std::vector<Interval>;
using Coordinates = std::vector<coordinate_t>;
using Distances = std::vector<distance_t>;
using Curve_Numbers = std::vector<curve_number_t>;
using Parameters = std::vector<parameter_t>;

template<typename T, std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
inline bool near_eq(T x, T y) {
  return std::abs(x - y) <= std::min(std::abs(x), std::abs(y)) * std::numeric_limits<T>::epsilon();
}


#endif