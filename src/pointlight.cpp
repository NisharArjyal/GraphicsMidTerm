
#include <cmath>
#include <iostream>


#include "pointlight.hpp"

PointLight::PointLight() {
  color_ = Vec3 {1.0, 1.0, 1.0};
  //location_ = Vec3 {0.0, 0.0, 0.0};
  intensity_ = 1.0;
}

PointLight::~PointLight() {

}

bool PointLight::compute_illumination(
  const Vec3& intpoint, 
  const Vec3& local_normal,
  const std::vector<std::shared_ptr<AbstractObject>>& objects,
  const std::shared_ptr<AbstractObject>& obj,
  Vec3& color, 
  double& intensity
  ) 
{
  //construct a unit vector pointing from the intersection point to the light  
  
  Vec3 light_dir = (location_ - intpoint).normalized();
  // std::cout << "Norm of light_dir : " << light_dir.norm() << '\n';
  // std::cout << light_dir.x_ << '\n'; 
  // std::cout << light_dir.y_ << '\n';
  // std::cout << light_dir.z_ << '\n';
  //compute a starting point

  Vec3 start = intpoint;
  //compute angle betn local ray and light ray
  //assume local_normal is a unit vector

  double angle = acos(local_normal.dot(light_dir));

  //if the angle is pointing away from the light then we have no illumination

  //pi/2
  if (angle > 1.5708) { 
    color = color_;
    intensity = 0.0;
    return false;
  } else {
    color = color_;
    intensity = intensity_ * (1.0 - angle / 1.5708);
    return true;
  }
  return true;
}
