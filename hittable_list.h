#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

class hittable_list : public Hittable {
public:
  hittable_list() {}
  hittable_list(std::shared_ptr<Hittable> object) { add(object); }

  void clear() { objects.clear(); }
  void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

  bool hit(const Ray& r, double t_min, double t_max, HittableProperties& properties) const override;

  std::vector<std::shared_ptr<Hittable>> objects;
};

bool hittable_list::hit(const Ray& r, double t_min, double t_max, HittableProperties& properties) const {
  HittableProperties temp_properties;
  bool hit_anything = false;
  auto closest_so_far = t_max;

  for (const auto& object : objects) {
    if (object->hit(r, t_min, closest_so_far, temp_properties)) {
      hit_anything = true;
      closest_so_far = temp_properties.t;
      properties = temp_properties;
    }
  }

  return hit_anything;
}
