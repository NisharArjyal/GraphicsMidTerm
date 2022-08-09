#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "vec3.hpp"
#include "ray.hpp"


class Camera {
  public:

    Camera();

    void set_position(const Vec3& newpos);
    void set_lookat(const Vec3& newlookat);
    void set_up(const Vec3& upvec);
    void set_length(double newlength);
    void set_horizontal_size(double newsize);
    void set_aspect_ratio(double newsize);

    Vec3 get_position();
    Vec3 get_lookat();
    Vec3 get_up();
    Vec3 get_u();
    Vec3 get_v();
    Vec3 get_screen_center();
    double get_length();
    double get_horizontal_size();
    double get_aspect();


    bool generate_ray(double proscreenx, double proscreeny, Ray& cam_ray);

    void update_camera_geometry();

  private: 
    Vec3 pos;
    Vec3 lookat;
    Vec3 up;
    double length;
    double horizontal_size;
    double aspect_ratio;

    Vec3 alignment_vector;
    Vec3 projection_screenU;
    Vec3 projection_screenV;
    Vec3 projection_screen_center;
};






















#endif
