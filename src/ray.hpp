#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

class Ray {
  public:
    Ray(); 

    Ray(const Vec3& point1, const Vec3& point2) ;

    Vec3 getpoint1() const;
    Vec3 getpoint2() const;

  //data
  Vec3 point1_;
  Vec3 point2_;
  Vec3 lab_;

};







#endif
