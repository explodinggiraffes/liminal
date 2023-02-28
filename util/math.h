#pragma once

#include <cstdlib>
#include <limits>

const double MIN_T = 0.001;
const double MAX_T = std::numeric_limits<double>::infinity();

/* Returns a random double in[0, 1). */
inline double RandomDouble() {
  return rand() / (RAND_MAX + 1.0);
}

/* Returns a random double in [min, max). */
inline double RandomDouble(double min, double max) {
  return min + (max - min) * RandomDouble();
}
