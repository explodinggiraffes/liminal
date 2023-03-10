#include "sphere.h"

#include <cmath>

bool Sphere::Hit(const Ray& ray, double t_min, double t_max, HittableProperties& properties) const {
  Vec3 oc = ray.origin() - center_;
  auto a = ray.direction().LengthSquared();
  auto half_b = DotProduct(oc, ray.direction());
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
  properties.p = ray.at(properties.t);
  Vec3 outward_normal = (properties.p - center_) / radius_;
  properties.SetFaceNormal(ray, outward_normal);
  properties.mat_ptr = material_;

  return true;
}
