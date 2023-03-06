#include <ctime>
#include <fstream>
#include <iostream>

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "ray.h"
#include "scene_builder.h"
#include "sphere.h"
#include "vec3.h"
#include "util/color.h"
#include "util/math.h"

// TODO: Make these non-const. Move to a configuration file and/or struct.
const auto aspect_ratio = 3.0 / 2.0;
//const int image_width = 1200;
const int image_width = 300;
const int image_height = static_cast<int>(image_width / aspect_ratio);
//const int samples_per_pixel = 500;
const int samples_per_pixel = 50;
//const int max_depth = 50;
const int max_depth = 5;

double hit_sphere(const Point3& center, double radius, const Ray& r) {
  Vec3 oc = r.origin() - center;
  auto a = r.direction().LengthSquared();
  auto half_b = DotProduct(oc, r.direction());
  auto c = oc.LengthSquared() - radius * radius;
  auto discriminant = half_b * half_b - a * c;

  if (discriminant < 0) {
    return -1.0;
  } else {
    return (-half_b - std::sqrt(discriminant)) / a;
  }
}

Color ray_color(const Ray& r, const Hittable& world, int depth) {
  HittableProperties properties;

  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0) {
    return Color(0, 0, 0);
  }

  if (world.hit(r, MIN_T, MAX_T, properties)) {
    Ray scattered;
    Color attenuation;
    if (properties.mat_ptr->Scatter(r, properties, attenuation, scattered)) {
      return attenuation * ray_color(scattered, world, depth - 1);
    }
    return Color(0, 0, 0);
  }

  Vec3 unit_direction = make_vec3::UnitVector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);

  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {
  std::cout << "Hello Liminal!\n";

  // Random numbers

  srand((unsigned int)time(0));

  // The scene

  hittable_list scene;
  SceneBuilder::RTOWBookCover(scene);

  // Camera
  // TODO: Move to a configuration file and/or struct.

  Point3 lookfrom(13, 2, 3);
  Point3 lookat(0, 0, 0);
  Vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  auto aperture = 0.1;

  Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

  // File

  std::ofstream image_file;
  image_file.open("images/image.ppm", std::ios::out);
  if (!image_file.is_open()) {
    std::cerr << "Unable to open file image.ppm for writing" << std::endl;
    return EXIT_FAILURE;
  }
  image_file << "P3\n" << image_width << " " << image_height << "\n255\n";

  // Render

  for (int j = image_height - 1; j >= 0; --j) {
    std::cout << "Scanlines remaining: " << j << "\n";
    for (int i = 0; i < image_width; ++i) {
      Color pixel_color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + RandomDouble()) / (image_width - 1);
        auto v = (j + RandomDouble()) / (image_height - 1);
        Ray r = cam.CalculateRay(u, v);
        pixel_color += ray_color(r, scene, max_depth);
      }
      WriteColorToStream(image_file, pixel_color, samples_per_pixel);
    }
  }

  image_file.close();

  std::cout << "Done.\n";

  return EXIT_SUCCESS;
}
