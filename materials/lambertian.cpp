#include "lambertian.h"

Lambertian::Lambertian(const Color& albedo) : albedo_(albedo) { }

bool Lambertian::Scatter(
    const Ray& r_in,
    const HittableProperties& properties,
    Color& out_ray_attenuation,
    Ray& out_scattered_ray) const {
  auto scatter_direction = properties.normal + make_vec3::RandomUnitVector();
  if (scatter_direction.IsNearZero()) {
    scatter_direction = properties.normal;
  }

  out_scattered_ray = Ray(properties.p, scatter_direction);
  out_ray_attenuation = albedo_;

  return true;
}
