#pragma once

#include <memory>

#include "hittable.h"

class Sphere : public Hittable {
public:
  Sphere(Point3 center, double radius, std::shared_ptr<Material> material)
      : center_(center), radius_(radius), material_(material) {
  };

  virtual bool Hit(const Ray& ray, double t_min, double t_max, HittableProperties& properties) const override;

private:
  std::shared_ptr<Material> material_;
  Point3 center_;
  double radius_ = 0.0;
};
