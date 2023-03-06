#include "hittable_objects.h"

void HittableObjects::Add(std::shared_ptr<Hittable> hittable) {
  hittable_objects_.push_back(hittable);
}

void HittableObjects::Clear() {
  hittable_objects_.clear();
}

bool HittableObjects::Hit(const Ray& ray, double t_min, double t_max, HittableProperties& properties) const {
  HittableProperties temp_properties;
  bool did_hit = false;
  auto closest_so_far = t_max;

  for (const auto& hittable : hittable_objects_) {
    if (hittable->Hit(ray, t_min, closest_so_far, temp_properties)) {
      did_hit = true;
      closest_so_far = temp_properties.t;
      properties = temp_properties;
    }
  }

  return did_hit;
}
