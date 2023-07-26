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
  Lambertian(const Color& albedo);

  bool Scatter(
      const Ray& r_in,
      const HittableProperties& properties,
      Color& out_ray_attenuation,
      Ray& out_scattered_ray) const override;

private:
  Color albedo_;
};
