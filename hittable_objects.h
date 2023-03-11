#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

class HittableObjects {
public:
  void Add(std::unique_ptr<Hittable> hittable);

  void Clear();

  bool Hit(const Ray& ray, double t_min, double t_max, HittableProperties& properties) const;

private:
  std::vector<std::unique_ptr<Hittable>> hittable_objects_;
};
