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
  Metal(const Color& albedo, double bluriness);

  bool Scatter(
      const Ray& r_in,
      const HittableProperties& properties,
      Color& out_ray_attenuation,
      Ray& out_scattered_ray) const override;

private:
  Color albedo_;
  double bluriness_;
};
