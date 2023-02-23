#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>

#include "camera.h"
#include "color_util.h"
#include "dielectric.h"
#include "hittable.h"
#include "hittable_list.h"
#include "lambertian.h"
#include "math_util.h"
#include "metal.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

const double infinity = std::numeric_limits<double>::infinity();
const auto aspect_ratio = 16.0 / 9.0;
const int image_width = 400;
const int image_height = static_cast<int>(image_width / aspect_ratio);
const int samples_per_pixel = 100;
const int max_depth = 50;

double hit_sphere(const point3& center, double radius, const ray& r) {
  vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;
  auto discriminant = half_b * half_b - a * c;

  if (discriminant < 0) {
    return -1.0;
  } else {
    return (-half_b - std::sqrt(discriminant)) / a;
  }
}

color ray_color(const ray& r, const hittable& world, int depth) {
  hit_record rec;

  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0) {
    return color(0, 0, 0);
  }

  if (world.hit(r, 0.001, infinity, rec)) {
    ray scattered;
    color attenuation;
    if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
      return attenuation * ray_color(scattered, world, depth - 1);
    }
    return color(0, 0, 0);
  }

  vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);

  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
  std::cout << "Hello Liminal!\n";

  // Random numbers

  srand((unsigned int)time(0));

  // World

  hittable_list world;

  auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto material_left = std::make_shared<dielectric>(1.5);
  auto material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

  world.add(std::make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(std::make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
  world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
  world.add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));


  // Camera

  point3 lookfrom(3, 3, 2);
  point3 lookat(0, 0, -1);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = (lookfrom - lookat).length();
  auto aperture = 2.0;

  camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

  // File

  std::ofstream image_file;
  image_file.open("image.ppm", std::ios::out);
  if (!image_file.is_open()) {
    std::cerr << "Unable to open file image.ppm for writing" << std::endl;
    return EXIT_FAILURE;
  }
  image_file << "P3\n" << image_width << " " << image_height << "\n255\n";

  // Render

  for (int j = image_height - 1; j >= 0; --j) {
    std::cout << "Scanlines remaining: " << j << "\n";
    for (int i = 0; i < image_width; ++i) {
      color pixel_color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_double()) / (image_width - 1);
        auto v = (j + random_double()) / (image_height - 1);
        ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, world, max_depth);
      }
      write_color(image_file, pixel_color, samples_per_pixel);
    }
  }

  image_file.close();

  std::cout << "Done.\n";

  return EXIT_SUCCESS;
}
