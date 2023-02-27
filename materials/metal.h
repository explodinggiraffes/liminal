#pragma once

#include "hittable.h"
#include "material.h"

/* ------------------------------------------------------------------------------------------------------------------
 * Material with specular reflection(s).
 *-----------------------------------------------------------------------------------------------------------------*/
class Metal : public Material {
public:
  /**
   * Creates a new metal material.
   *
   * \param albedo: proportion of light reflected away from a surface.
   * \param bluriness: reflection blurriness caused by bumps or pits on the material's surface.
   */
  Metal(const color& albedo, double bluriness) : albedo_(albedo), bluriness_(bluriness < 1.0 ? bluriness : 1.0) { }

  bool Scatter(
      const ray& r_in,
      const hit_record& rec,
      color& out_ray_attenuation,
      ray& out_scattered_ray) const override {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    
    out_scattered_ray = ray(rec.p, reflected + bluriness_ * random_in_unit_sphere());
    out_ray_attenuation = albedo_;

    return (dot(out_scattered_ray.direction(), rec.normal) > 0);
  }

private:
  color albedo_;
  double bluriness_;
};
