#include "metal.h"

Metal::Metal(const Color& albedo, double bluriness) : albedo_(albedo), bluriness_(bluriness < 1.0 ? bluriness : 1.0) { }

bool Metal::Scatter(
    const Ray& r_in,
    const HittableProperties& properties,
    Color& out_ray_attenuation,
    Ray& out_scattered_ray) const {
  Vec3 reflected = Reflect(make_vec3::UnitVector(r_in.direction()), properties.normal);

  out_scattered_ray = Ray(properties.p, reflected + bluriness_ * make_vec3::RandomInUnitSphere());
  out_ray_attenuation = albedo_;

  return (DotProduct(out_scattered_ray.direction(), properties.normal) > 0);
}
