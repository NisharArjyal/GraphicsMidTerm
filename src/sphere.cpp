#include "sphere.hpp"
#include <cmath>

Sphere::Sphere() {
}

Sphere::~Sphere() {

}

bool Sphere::intersection_test(
      const Ray& ray,
      Vec3& intersection_point,
      Vec3& local_normal,
      Vec3& local_color
    ) 
{
  //copy the ray and apply the backwards transform

  Ray backray = transform.apply(ray, BCKTFORM);//world to local
    

  Vec3 vhat = backray.lab_;
  vhat.normalize();

  //auto a = 1.0;
    
  auto first_point = backray.point1_;
  auto second_point = backray.point2_;
  
  double b =  2.0 * first_point.dot(vhat);
  double c = first_point.dot(first_point) - 1.0;

  double inttest = (b * b) - 4.0 * c;

  Vec3 poi;

  if (inttest > 0.0) {
	double numSQRT = sqrtf(inttest);
	double t1 = (-b + numSQRT) / 2.0;
	double t2 = (-b - numSQRT) / 2.0;
	
	/* If either t1 or t2 are negative, then at least part of the object is
		behind the camera and so we will ignore it. */
	if ((t1 < 0.0) || (t2 < 0.0)) {
		return false;
	} else {
		// Determine which point of intersection was closest to the camera.
		if (t1 < t2) {
			poi = backray.point1_ + (vhat * t1);
		} else {
			poi = backray.point1_ + (vhat * t2);
		}

		intersection_point = transform.apply(poi, FWDTFORM);
        Vec3 origin = Vec3 {0.0, 0.0, 0.0};
        Vec3 neworigin = transform.apply(origin, FWDTFORM);
		local_normal = intersection_point - neworigin;
		local_normal.normalize();

        local_color = base_color;
	}
      return true;
  } else {
    return false;
  }

}

