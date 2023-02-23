#pragma once

#include "hittable.h"
#include "material.h"

class metal : public material {
public:
  metal(const color& a, double f) : albedo(a), fuzz(f < 1.0 ? f : 1.0) { }

  virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;

    return (dot(scattered.direction(), rec.normal) > 0);
  }

  color albedo;
  double fuzz;
};
