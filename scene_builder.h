#pragma once

#include <memory>

#include "hittable_list.h"
#include "sphere.h"
#include "materials/dielectric.h"
#include "materials/lambertian.h"
#include "materials/metal.h"

/* ------------------------------------------------------------------------------------------------------------------
 * Populates a scene with spheres made from different materials.
 *-----------------------------------------------------------------------------------------------------------------*/
class SceneBuilder {
public:
  /**
   * Creates a scene for Image 20 from "Ray Tracing in One Weekend".
   */ 
  static void RTOWImage20(HittableObjects& out_scene) {
    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));

    auto material_left_sphere = std::make_shared<Dielectric>(1.5);
    auto material_center_sphere = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_right_sphere = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

    out_scene.add(std::make_shared<sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    out_scene.add(std::make_shared<sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center_sphere));
    out_scene.add(std::make_shared<sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left_sphere));
    out_scene.add(std::make_shared<sphere>(Point3(-1.0, 0.0, -1.0), -0.45, material_left_sphere));
    out_scene.add(std::make_shared<sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right_sphere));
  }

  /**
   * Creates a scene for the book cover image from "Ray Tracing in One Weekend".
   */
  static void RTOWBookCover(HittableObjects& out_scene) {
    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    out_scene.add(std::make_shared<sphere>(Point3(0, -1000, 0), 1000, ground_material));

    //for (int start_x_index = -11; start_x_index < 11; ++start_x_index) {
    for (int start_x_index = -5; start_x_index < 5; ++start_x_index) {
      //for (int start_y_index = -11; start_y_index < 11; ++start_y_index) {
      for (int start_y_index = -5; start_y_index < 5; ++start_y_index) {
        auto random_material = RandomDouble();
        Point3 center(start_x_index + 0.9 * RandomDouble(), 0.2, start_y_index + 0.9 * RandomDouble());

        if ((center - Point3(4, 0.2, 0)).Length() > 0.9) {
          std::shared_ptr<Material> sphere_material;

          if (random_material < 0.8) {
            auto albedo = Color::Random() * Color::Random();
            sphere_material = std::make_shared<Lambertian>(albedo);
            out_scene.add(std::make_shared<sphere>(center, 0.2, sphere_material));
          }
          else if (random_material < 0.95) {
            auto albedo = Color::Random(0.5, 1);
            auto bluriness = RandomDouble(0, 0.5);
            sphere_material = std::make_shared<Metal>(albedo, bluriness);
            out_scene.add(std::make_shared<sphere>(center, 0.2, sphere_material));
          }
          else {
            sphere_material = std::make_shared<Dielectric>(1.5);
            out_scene.add(std::make_shared<sphere>(center, 0.2, sphere_material));
          }
        }
      }
    }

    out_scene.add(std::make_shared<sphere>(Point3(0, 1, 0), 1.0, std::make_shared<Dielectric>(1.5)));
    out_scene.add(std::make_shared<sphere>(Point3(-4, 1, 0), 1.0, std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1))));
    out_scene.add(std::make_shared<sphere>(Point3(4, 1, 0), 1.0, std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0)));
  }
};
