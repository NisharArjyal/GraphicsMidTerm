#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "light.hpp"


class PointLight : public AbstractLight {
  public:
  PointLight();
  virtual ~PointLight() override;
  virtual bool compute_illumination(
      const Vec3& intpoint, 
      const Vec3& local_normal,
      const std::vector<std::shared_ptr<AbstractObject>>& objects,
      const std::shared_ptr<AbstractObject>& obj,
      Vec3& color, 
      double& intensity
      ) override;
};


#endif
