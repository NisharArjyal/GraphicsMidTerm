#include "object.hpp"
#include <cmath>

#define EPSILON 1e-21f

AbstractObject::AbstractObject() {

}

AbstractObject::~AbstractObject() {

}


bool AbstractObject::intersection_test(
      const Ray& ray,
      Vec3& intersection_point,
      Vec3& local_normal,
      Vec3& local_color
    )
{
  return false;
}

bool AbstractObject::isclose(const double f1, const double f2) {
  return fabs(f1-f2) < EPSILON;
}


void AbstractObject::set_transform(Transform& transform_) {
    transform = transform_;
}






