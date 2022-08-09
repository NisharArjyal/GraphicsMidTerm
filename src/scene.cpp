#include <iostream>

#include "scene.hpp"



Scene::Scene() {
  //configure our camera
  cam.set_position(Vec3 {0.0, -10.0, 0.0});
  cam.set_lookat(Vec3 {0.0, 0.0, 0.0});
  cam.set_up(Vec3{0.0, 0.0, 1.0});
  cam.set_horizontal_size(0.25);
  cam.set_aspect_ratio( 16.0 / 9.0 );
  cam.update_camera_geometry();

  //construct a test sphere
  objects.push_back(std::make_shared<Sphere>(Sphere()));
  objects.push_back(std::make_shared<Sphere>(Sphere()));
  objects.push_back(std::make_shared<Sphere>(Sphere()));

//modify spheres

  Transform test1, test2, test3; 
  test1.set_transform(Vec3 {-1.5, 0.0, 0.0}, Vec3 {0.f,0.f,0.f}, Vec3{0.5, 0.5, 0.75});
  test2.set_transform(Vec3 {0.0, 0.0, 0.0}, Vec3 {0.f,0.f,0.f}, Vec3{0.75, 0.5, 0.5});
  test3.set_transform(Vec3 {1.5, 0.0, 0.0}, Vec3 {0.f,0.f,0.f}, Vec3{0.75, 0.75, 0.75});

  objects.at(0)->set_transform(test1);
  objects.at(1)->set_transform(test2);
  objects.at(2)->set_transform(test3);

  objects.at(0)->base_color = Vec3 {64.f, 128.f, 200.f};
  objects.at(1)->base_color = Vec3{255.0, 128.0, 0.0};
  objects.at(2)->base_color = Vec3{255.0, 200.0, 0.0};

  lights.push_back(std::make_shared<PointLight>(PointLight()));
  lights.at(0) -> location_ = Vec3 {5.0, -10.0, -5.0};
  lights.at(0) -> color_ = Vec3 {255.0, 255.0, 255.0};
}


bool Scene::render(Image& image) {
  //get the dimension of the output image
  int xsize = image.xsize; 
  int ysize = image.ysize; 

  //loop over each pixel in image
  
  Ray camray;
  Vec3 intpoint;
  Vec3 local_normal;
  Vec3 local_color;

  double xfact = 1.0 / (static_cast<double>(xsize) / 2.0);
  double yfact = 1.0 / (static_cast<double>(ysize) / 2.0);
  double minimum_distance = 1e6;
  double maximum_distance = 0.0;

  for (int i = 0; i < xsize; ++i) {
    for (int j = 0; j < ysize; ++j) {
      double normx = (static_cast<double>(i) * xfact) - 1.0;
      double normy = (static_cast<double>(j) * yfact) - 1.0;
      cam.generate_ray(normx, normy, camray);

      //test for intersections with all the objects in our scene

      for (auto obj : objects) {
        bool valid_int = obj -> intersection_test(
            camray, 
            intpoint,
            local_normal,
            local_color
        );
      
        if (valid_int) {
          //compute intensity of illumination 
          
          double intensity;
          Vec3 color;
          bool valid_illum = false;

          for (auto light : lights) {
            valid_illum = light->compute_illumination(
                intpoint, 
                local_normal, 
                objects,
                obj,
                color, 
                intensity
              );
          }

          double distance = (intpoint - camray.point1_).norm();

          if (distance > maximum_distance) {
            maximum_distance = distance;
          }

          if (distance < minimum_distance) {
            minimum_distance = distance;
          }

				  //image.setpixel(i, j, 255.0 - ((distance - 9.0) / 0.94605) * 255.0, 0.0, 0.0);
				  if (valid_illum) {
				    // image.setpixel(i, j, 255.0 * intensity, 0.0, 0.0);
				    image.setpixel(i, j, local_color.x_ * intensity,local_color.y_ * intensity, local_color.z_ * intensity);
				  } else {
				    //image.setpixel(i, j, 0.0, 0.0, 0.0);
				  }

        } else {
				  //image.setpixel(i, j, 0.0, 0.0, 0.0);
        }

      }
    }

  }

  std::cout << "Minimum Distance : "<< minimum_distance << '\n';
  std::cout << "Maximum Distance :" << maximum_distance << '\n';

  return true;
}



