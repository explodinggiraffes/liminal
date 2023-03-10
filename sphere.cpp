#include "sphere.h"

#include <cmath>

bool Sphere::Hit(const Ray& r, double t_min, double t_max, HittableProperties& properties) const {
  Vec3 oc = r.origin() - center_;
  auto a = r.direction().LengthSquared();
  auto half_b = DotProduct(oc, r.direction());
  auto c = oc.LengthSquared() - radius_ * radius_;

  auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0) return false;
  auto sqrtd = std::sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root)
      return false;
  }

  properties.t = root;
  properties.p = r.at(properties.t);
  Vec3 outward_normal = (properties.p - center_) / radius_;
  properties.SetFaceNormal(r, outward_normal);
  properties.mat_ptr = material_;

  return true;
}
