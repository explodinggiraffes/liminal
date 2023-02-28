#pragma once

#include <cmath>
#include <iostream>

#include "util/math.h"

class Vec3 final {
public:
  Vec3() : component{0.0, 0.0, 0.0} { }

  Vec3(double e0, double e1, double e2) : component{e0, e1, e2} { }

  double x() const { return component[0]; }
  double y() const { return component[1]; }
  double z() const { return component[2]; }

  double r() const { return component[0]; }
  double g() const { return component[1]; }
  double b() const { return component[2]; }

  Vec3 operator-() const { return Vec3(-component[0], -component[1], -component[2]); }
  Vec3& operator/=(const double t) { return *this *= 1 / t; }

  double operator[](int i) const { return component[i]; }
  double& operator[](int i) { return component[i]; }

  Vec3& operator+=(const Vec3& v) {
    component[0] += v.component[0];
    component[1] += v.component[1];
    component[2] += v.component[2];
    return *this;
  }

  Vec3& operator*=(const double t) {
    component[0] *= t;
    component[1] *= t;
    component[2] *= t;
    return *this;
  }

  /* Returns true if the vector is close to zero in all dimensions. */
  bool IsNearZero() const {
    const auto s = 1e-8;
    return (std::fabs(component[0]) < s) && (std::fabs(component[1]) < s) && (std::fabs(component[2]) < s);
  }

  double Length() const {
    return std::sqrt(LengthSquared());
  }

  double LengthSquared() const {
    return component[0] * component[0] + component[1] * component[1] + component[2] * component[2];
  }

  static Vec3 Random() {
    return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
  }

  static Vec3 Random(double min, double max) {
    return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
  }

private:
  double component[3];
};

using Point3 = Vec3;
using Color = Vec3;

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
  return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v) {
  return Vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
  return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline Vec3 operator*(double t, const Vec3& v) {
  return Vec3(t * v[0], t * v[1], t * v[2]);
}

inline Vec3 operator*(const Vec3& v, double t) {
  return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
  return (1 / t) * v;
}

inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
  return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline double DotProduct(const Vec3& u, const Vec3& v) {
  return
    u[0] * v[0] +
    u[1] * v[1] +
    u[2] * v[2];
}

inline Vec3 CrossProduct(const Vec3& u, const Vec3& v) {
  return Vec3(
    u[1] * v[2] - u[2] * v[1],
    u[2] * v[0] - u[0] * v[2],
    u[0] * v[1] - u[1] * v[0]);
}

inline Vec3 Reflect(const Vec3& v, const Vec3& n) {
  return v - 2 * DotProduct(v, n) * n;
}

inline Vec3 Refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
  auto cos_theta = fmin(DotProduct(-uv, n), 1.0);
  Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
  Vec3 r_out_parallel = -std::sqrt(fabs(1.0 - r_out_perp.LengthSquared())) * n;
  return r_out_perp + r_out_parallel;
}

namespace make_vec3 {
inline Vec3 UnitVector(Vec3 v) {
  return v / v.Length();
}

inline Vec3 RandomInUnitSphere() {
  while (true) {
    auto p = Vec3::Random(-1.0, 1.0);
    if (p.LengthSquared() >= 1) continue;
    return p;
  }
}

inline Vec3 RandomInUnitDisk() {
  while (true) {
    auto p = Vec3(RandomDouble(-1.0, 1.0), RandomDouble(-1.0, 1.0), 0.0);
    if (p.LengthSquared() >= 1) continue;
    return p;
  }
}

inline Vec3 RandomUnitVector() {
  return UnitVector(RandomInUnitSphere());
}
}
