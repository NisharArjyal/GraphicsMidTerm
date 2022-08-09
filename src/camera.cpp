#include "camera.hpp"
#include "ray.hpp"
//#include "vec3.hpp"

Camera::Camera() {
  pos = Vec3{0.0, -10.0, 0.0};
  lookat = Vec3 {0.0, 0.0, 0.0};
  up =  Vec3 {0.0, 0.0, 1.0};
  length = 1.0;
  horizontal_size = 1.0;
  aspect_ratio = 1.0;
}

void Camera::set_position(const Vec3& newpos) {
  pos = newpos;
}

void Camera::set_lookat(const Vec3& newlookat) {
  lookat = newlookat;

}

void Camera::set_up(const Vec3& upvec) {
  up = upvec;
}

void Camera::set_length(double newlength) {
  length = newlength;
}

void Camera::set_horizontal_size(double newsize) {
  horizontal_size = newsize;
}

void Camera::set_aspect_ratio(double newaspect) {
  aspect_ratio = newaspect;   
}

Vec3 Camera::get_position() {
  return pos;
}

Vec3 Camera::get_lookat() {
  return lookat;
}

Vec3 Camera::get_up() {
  return up;
}

Vec3 Camera::get_u() {
  return projection_screenU; 
}

Vec3 Camera::get_v() {
  return projection_screenV;
}

Vec3 Camera::get_screen_center() {
  return projection_screen_center;
}

double Camera::get_length() {
  return length;
}

double Camera::get_horizontal_size() {
  return horizontal_size;
}

double Camera::get_aspect() {
  return aspect_ratio;
}

bool Camera::generate_ray(double proscreenx, double proscreeny, Ray& cam_ray) {
	// compute the location of the screen_point in world coordinate
	Vec3 screenworldpart1 = projection_screen_center + (projection_screenU * proscreenx);
	Vec3 screenworldcoordinate = screenworldpart1 + (projection_screenV * proscreeny);
	cam_ray.point1_ = this->pos;
	cam_ray.point2_ = screenworldcoordinate;
	cam_ray.lab_ = screenworldcoordinate - this->pos;
	return true;
}

void Camera::update_camera_geometry() {
  //compute the vector from camera position to lookat position 
  alignment_vector = lookat - pos;
  alignment_vector.normalize();

  //compute alpha and beta unit vectors
  projection_screenU = alignment_vector.cross(up);
  projection_screenU.normalize();
  projection_screenV = projection_screenU.cross(alignment_vector);
  projection_screenV.normalize();
  
  //compute the position of center of the screen
  projection_screen_center = pos + (length * alignment_vector);

  //modify 'u' and 'v' to match the size and aspect_ratio.
	projection_screenU = projection_screenU * horizontal_size;
	projection_screenV = projection_screenV * (horizontal_size / aspect_ratio);
}



