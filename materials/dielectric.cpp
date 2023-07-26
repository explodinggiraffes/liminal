#include "dielectric.h"

#include <cmath>

Dielectric::Dielectric(double index_of_refraction) : index_of_refraction_(index_of_refraction) { }

bool Dielectric::Scatter(
    const Ray& r_in,
    const HittableProperties& properties,
    Color& out_ray_attenuation,
    Ray& out_scattered_ray) const {
  Vec3 unit_direction = make_vec3::UnitVector(r_in.direction());
  double cos_theta = std::fmin(DotProduct(-unit_direction, properties.normal), 1.0);
  double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
  double refraction_ratio = properties.front_face ? (1.0 / index_of_refraction_) : index_of_refraction_;
  bool cannot_refract = refraction_ratio * sin_theta > 1.0;

  Vec3 direction;
  if (cannot_refract || Reflectance(cos_theta, refraction_ratio) > RandomDouble()) {
    direction = Reflect(unit_direction, properties.normal);
  }
  else {
    direction = Refract(unit_direction, properties.normal, refraction_ratio);
  }

  out_scattered_ray = Ray(properties.p, direction);
  out_ray_attenuation = Color(1.0, 1.0, 1.0);

  return true;
}

double Dielectric::Reflectance(double cosine, double reflection_coefficient) {
  auto r0 = (1.0 - reflection_coefficient) / (1.0 + reflection_coefficient);
  r0 = r0 * r0;
  return r0 + (1.0 - r0) * pow((1.0 - cosine), 5.0);
}
