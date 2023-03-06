#pragma once

#include "ray.h"
#include "vec3.h"

struct HittableProperties;

/* ------------------------------------------------------------------------------------------------------------------
 * Base class used by materials.
 *-----------------------------------------------------------------------------------------------------------------*/
class Material {
public:
  /**
   * Scatter a ray of light that hits a material's surface.
   *
   * \return true if a ray should be used as part of lighting calculations, false if not.
   */
  virtual bool Scatter(
    const Ray& r_in,
    const HittableProperties& properties,
    Color& out_ray_attenuation,
    Ray& out_scattered_ray) const = 0;

  virtual ~Material() = default;
};
