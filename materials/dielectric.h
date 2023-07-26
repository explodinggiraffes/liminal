#pragma once

#include "hittable.h"
#include "material.h"

/* ------------------------------------------------------------------------------------------------------------------
 * Material representing a clear surface such as water, glass, and diamond.
 * Example reflective indexes: air 1, water 1.3, glass 1.5 - 1.7, diamond 1.8 - 2.4.
 *-----------------------------------------------------------------------------------------------------------------*/
class Dielectric : public Material {
public:
  /**
   * Creates a new dielectric material.
   *
   * \param index_of_refraction: the amount that light is bent when traveling from one medium to another.
   */
  Dielectric(double index_of_refraction);

  bool Scatter(
      const Ray& r_in,
      const HittableProperties& properties,
      Color& out_ray_attenuation,
      Ray& out_scattered_ray) const override;

private:
  /**
   * Use Schlick's approximation for reflectance (e.g., glass has reflectivity that varies with the viewing angle).
   * See Schlick's approximation: https://en.wikipedia.org/wiki/Schlick%27s_approximation
   */
  static double Reflectance(double cosine, double reflection_coefficient);

  double index_of_refraction_;
};
