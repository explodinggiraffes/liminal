#pragma once

#include <cmath>
#include <memory>

#include "hittable.h"
#include "vec3.h"

class sphere : public Hittable {
public:
  sphere() { }
  sphere(Point3 cen, double r, std::shared_ptr<Material> m) : center(cen), radius(r), mat_ptr(m) { };

  virtual bool Hit(const Ray& r, double t_min, double t_max, HittableProperties& rec) const override;

  std::shared_ptr<Material> mat_ptr;
  Point3 center;
  double radius = 0.0;
};

bool sphere::Hit(const Ray& r, double t_min, double t_max, HittableProperties& rec) const {
  Vec3 oc = r.origin() - center;
  auto a = r.direction().LengthSquared();
  auto half_b = DotProduct(oc, r.direction());
  auto c = oc.LengthSquared() - radius * radius;

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

  rec.t = root;
  rec.p = r.at(rec.t);
  Vec3 outward_normal = (rec.p - center) / radius;
  rec.SetFaceNormal(r, outward_normal);
  rec.mat_ptr = mat_ptr;

  return true;
}
