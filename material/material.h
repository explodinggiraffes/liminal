#pragma once

#include "ray.h"
#include "vec3.h"

struct hit_record;

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
    const ray& r_in,
    const hit_record& rec,
    color& out_ray_attenuation,
    ray& out_scattered_ray) const = 0;

  virtual ~Material() { }
};
