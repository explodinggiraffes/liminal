#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>

#include "vec3.h"

void WriteColorToStream(std::ostream& out, Color pixel_color, int samples_per_pixel) {
  auto r = pixel_color.r();
  auto g = pixel_color.g();
  auto b = pixel_color.b();

  // Divide the color by the number of samples and gamma-correct for gamma 2.0.
  auto scale = 1.0 / samples_per_pixel;
  r = std::sqrt(scale * r);
  g = std::sqrt(scale * g);
  b = std::sqrt(scale * b);

  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(256 * std::clamp(r, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * std::clamp(g, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * std::clamp(b, 0.0, 0.999)) << '\n';
}
