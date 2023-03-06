#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

class HittableObjects : public Hittable {
public:
  void Add(std::shared_ptr<Hittable> hittable);

  void Clear();

  bool Hit(const Ray& ray, double t_min, double t_max, HittableProperties& properties) const override;

private:
  std::vector<std::shared_ptr<Hittable>> hittable_objects_;
};
