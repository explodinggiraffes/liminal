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
  Metal(const Color& albedo, double bluriness) : albedo_(albedo), bluriness_(bluriness < 1.0 ? bluriness : 1.0) { }

  bool Scatter(
      const Ray& r_in,
      const hit_record& rec,
      Color& out_ray_attenuation,
      Ray& out_scattered_ray) const override {
    Vec3 reflected = Reflect(make_vec3::UnitVector(r_in.direction()), rec.normal);
    
    out_scattered_ray = Ray(rec.p, reflected + bluriness_ * make_vec3::RandomInUnitSphere());
    out_ray_attenuation = albedo_;

    return (DotProduct(out_scattered_ray.direction(), rec.normal) > 0);
  }

private:
  Color albedo_;
  double bluriness_;
};
