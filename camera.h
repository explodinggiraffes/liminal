#pragma once

#include "ray.h"
#include "vec3.h"

class Camera final {
public:
  /**
   * Creates a new camera.
   *
   * \param look_from: The camera's position.
   * \param look_at: The position that the camera is looking at.
   * \param up: Camera roll (sideways tilt).
   * \param vertical_fov: Vertical field of view (top to bottom) in degrees.
   * \param aspect_ratio: Film aspect ratio.
   * \param aperture: Camera opening through which light travels. Increasing the aperture decreases the depth of field
   * (increases defocus blur).
   * \param focus_distance: The distance between the lens and the film plane.
   */
  Camera(
    Point3 look_from,
    Point3 look_at,
    Vec3   up,
    double vertical_fov,
    double aspect_ratio,
    double aperture,
    double focus_distance
  );

  /* Calculates a ray for the supplied position. */
  Ray CalculateRay(double s, double t) const;

private:
  Point3 look_from_;
  Point3 lower_left_corner_;
  Vec3 horizontal_;
  Vec3 vertical_;
  Vec3 u_, v_, w_;
  double lens_radius_;
};
