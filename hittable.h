#pragma once

#include <memory>

#include "ray.h"
#include "materials/material.h"

struct HittableProperties {
  std::shared_ptr<Material> mat_ptr;
  Point3 p;
  Vec3 normal;
  double t = 0.0;
  bool front_face = true;

  inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {
    front_face = DotProduct(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class Hittable {
public:
  virtual bool hit(const Ray& r, double t_min, double t_max, HittableProperties& properties) const = 0;
};
