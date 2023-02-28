#include "camera.h"

#include <cmath>
#include <numbers>

Camera::Camera(
    Point3 look_from,
    Point3 look_at,
    Vec3   up,
    double vertical_fov,
    double aspect_ratio,
    double aperture,
    double focus_distance) {
  auto theta = vertical_fov * (std::numbers::pi / 180.0);
  auto ratio_of_vertical_field_of_view_to_z = std::tan(theta / 2.0);
  auto viewport_height = ratio_of_vertical_field_of_view_to_z * 2.0;
  auto viewport_width = viewport_height * aspect_ratio;

  w_ = make_vec3::UnitVector(look_from - look_at);
  u_ = make_vec3::UnitVector(CrossProduct(up, w_));
  v_ = CrossProduct(w_, u_);

  look_from_ = look_from;
  horizontal_ = focus_distance * viewport_width * u_;
  vertical_ = focus_distance * viewport_height * v_;
  lower_left_corner_ = look_from_ - horizontal_ / 2.0 - vertical_ / 2.0 - focus_distance * w_;
  lens_radius_ = aperture / 2.0;
}

Ray Camera::CalculateRay(double s, double t) const {
  Vec3 random_point_on_lens = lens_radius_ * make_vec3::RandomInUnitDisk();
  Vec3 offset = u_ * random_point_on_lens.x() + v_ * random_point_on_lens.y();

  return Ray(
    look_from_ + offset,
    lower_left_corner_ + s * horizontal_ + t * vertical_ - look_from_ - offset
  );
}
