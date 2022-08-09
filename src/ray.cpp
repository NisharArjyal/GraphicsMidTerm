#include "ray.hpp"


Ray::Ray() {
  point1_ = Vec3 {0.0, 0.0, 0.0};
  point2_ = Vec3 {0.0, 0.0, 0.1};
  lab_ = point2_ - point1_;
}

Ray::Ray(const Vec3& point1, const Vec3& point2) {
  point1_ = point1; 
  point2_ = point2; 
  lab_    = point2_ - point1_;
}

Vec3 Ray::getpoint1() const {
  return point1_;
}

Vec3 Ray::getpoint2() const {
  return point2_;
}
