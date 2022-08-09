#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "object.hpp"
#include "transform.hpp"

class Sphere : public AbstractObject {
public: 
  Sphere();
  virtual ~Sphere() override;

  virtual bool intersection_test(
      const Ray& ray,
      Vec3& intersection_point,
      Vec3& local_normal,
      Vec3& local_color
    ) override;



};


#endif
