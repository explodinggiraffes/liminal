#pragma once

#include <cmath>

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
  Dielectric(double index_of_refraction) : index_of_refraction_(index_of_refraction) { }

  bool Scatter(
      const Ray& r_in,
      const hit_record& rec,
      Color& out_ray_attenuation,
      Ray& out_scattered_ray) const override {
    Vec3 unit_direction = make_vec3::UnitVector(r_in.direction());
    double cos_theta = std::fmin(DotProduct(-unit_direction, rec.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
    double refraction_ratio = rec.front_face ? (1.0 / index_of_refraction_) : index_of_refraction_;
    bool cannot_refract = refraction_ratio * sin_theta > 1.0;

    Vec3 direction;
    if (cannot_refract || Reflectance(cos_theta, refraction_ratio) > RandomDouble()) {
      direction = Reflect(unit_direction, rec.normal);
    }
    else {
      direction = Refract(unit_direction, rec.normal, refraction_ratio);
    }

    out_scattered_ray = Ray(rec.p, direction);
    out_ray_attenuation = Color(1.0, 1.0, 1.0);

    return true;
  }

private:
  /**
   * Use Schlick's approximation for reflectance (e.g., glass has reflectivity that varies with the viewing angle).
   * See Schlick's approximation: https://en.wikipedia.org/wiki/Schlick%27s_approximation
   */
  static double Reflectance(double cosine, double reflection_coefficient) {
    auto r0 = (1.0 - reflection_coefficient) / (1.0 + reflection_coefficient);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * pow((1.0 - cosine), 5.0);
  }

  double index_of_refraction_;
};
