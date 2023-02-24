#pragma once

#include "hittable.h"
#include "material.h"

/* ------------------------------------------------------------------------------------------------------------------
 * Material representing an ideal matte / diffusely reflecting surface.
 * The apparent brightness of a Lambertian surface to an observer is the same regardless of the observer's angle of
 * view.
 *-----------------------------------------------------------------------------------------------------------------*/
class Lambertian : public Material {
public:
  /**
   * Creates a new Lambertian material.
   *
   * \param albedo: proportion of light reflected away from a surface.
   */
  Lambertian(const color& albedo) : albedo_(albedo) { }

  bool Scatter(
      const ray& r_in,
      const hit_record& rec,
      color& out_ray_attenuation,
      ray& out_scattered_ray) const override {
    auto scatter_direction = rec.normal + random_unit_vector();
    if (scatter_direction.near_zero()) {
      scatter_direction = rec.normal;
    }

    out_scattered_ray = ray(rec.p, scatter_direction);
    out_ray_attenuation = albedo_;

    return true;
  }

private:
  color albedo_;
};
