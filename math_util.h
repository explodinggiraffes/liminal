#pragma once

#include <cstdlib>

const double PI = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
  return degrees * PI / 180.0;
}

// Returns a random double in [0, 1).
inline double random_double() {
  return rand() / (RAND_MAX + 1.0);
}

// Returns a random double in [min, max).
inline double random_double(double min, double max) {
  return min + (max - min) * random_double();
}
