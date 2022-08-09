#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "vec3.hpp"
#include "ray.hpp"
#include "transform.hpp"

class AbstractObject {

public:

  AbstractObject();

  virtual ~AbstractObject();


  virtual bool intersection_test(
      const Ray& ray,
      Vec3& intersection_point,
      Vec3& local_normal,
      Vec3& local_color
    );

  //function to accept the transform matrix
  void set_transform(Transform& transform_);

  bool isclose(const double f1, const double f2);

  public: 
    Vec3 base_color;
    Transform transform;

};






#endif
