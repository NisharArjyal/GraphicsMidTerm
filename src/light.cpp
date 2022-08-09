#include "light.hpp"


AbstractLight::AbstractLight() {

}

AbstractLight::~AbstractLight() {

}


bool AbstractLight::compute_illumination(
        const Vec3& intpoint, 
        const Vec3& local_normal,
        const std::vector<std::shared_ptr<AbstractObject>>& objects,
        const std::shared_ptr<AbstractObject>& obj,
        Vec3& color, 
        double& intensity
  ) 
{
  return false;
}
