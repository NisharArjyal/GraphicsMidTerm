
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP


#define _USE_MATH_DEFINES
#include <cmath>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>


// #include "vec3.hpp"
// #include "ray.hpp"

inline double to_radians(float degree) {
  return M_PI / 180.0 * degree;
}


class Transform {
  public:

  glm::mat4 m_;
  glm::mat4 minv_;

  Transform() 
  :m_{glm::mat4(1.)}
  ,minv_{glm::inverse(m_)}
  {}

  Transform(const glm::mat4& input) 
    :m_{input}
    ,minv_{glm::inverse(input)}
  {}

  Transform(const glm::mat4& mat, const glm::mat4& minv) 
    :m_{mat}
    ,minv_{minv}
  {}
  
  Transform inverse() const {
    return Transform{minv_, m_};
  }

  Transform transpose() const {
    return Transform{
      glm::transpose(m_),
      glm::transpose(minv_)
    };
  }

  //take a vector of deltas for the translation 
  //along each dimension.
  //remember a translation can only be applied to a point 
  //translation leaves vectors unchanged.
  static Transform translate(const Vec3& vec) {
    glm::mat4 mat(1, 0, 0, vec.x(),
                  0, 1, 0, vec.y(),
                  0, 0, 1, vec.z(),
                  0, 0, 0,      1);

    glm::mat4 matinv(1, 0, 0, -vec.x(),
                     0, 1, 0, -vec.y(),
                     0, 0, 1, -vec.z(),
                     0, 0, 0,      1);

    return Transform{ 
      mat,
      matinv
    };
  }

  static Transform scale(float x, float y, float z) {
    assert(x != 0 && y != 0 && z != 0);

    glm::mat4 mat(x, 0, 0, 0, 
                  0, y, 0, 0, 
                  0, 0, z, 0, 
                  0, 0, 0, 1);

    glm::mat4 matinv(1/x, 0, 0, 0,
                     0, 1/y, 0, 0,
                     0, 0, 1/z, 0,
                     0, 0, 0, 1);

    return Transform{ 
      mat,
      matinv
    };
  }

  //theta is passed in degrees, rotateX auto 
  //uses it in radians
  static Transform rotateX(float theta) {
    auto radtheta = to_radians(theta);
    float sintheta = std::sin(radtheta);
    float costheta = std::cos(radtheta);

    glm::mat4 mat(1,        0,         0, 0,
                  0, costheta, -sintheta, 0,
                  0, sintheta,  costheta, 0,
                  0,        0,         0, 1);
  
    return Transform{mat, glm::transpose(mat)};
  }

  //theta is passed in degrees, rotateX auto 
  //uses it in radians
  [[nodiscard]] static Transform rotateY(float theta) noexcept {
    auto radtheta = to_radians(theta);
    float sintheta = std::sin(radtheta);
    float costheta = std::cos(radtheta);

    glm::mat4 mat( costheta, 0, sintheta, 0,
                  0,         1, 0,        0,
                  -sintheta, 0, costheta, 0,
                  0,         0,        0, 1);
  
    return Transform{mat, glm::transpose(mat)};
  }

  //theta is passed in degrees, rotateX auto 
  //uses it in radians
  [[nodiscard]] static Transform rotateZ(float theta) noexcept {
    auto radtheta = to_radians(theta);
    float sintheta = std::sin(radtheta);
    float costheta = std::cos(radtheta);

    glm::mat4 mat(costheta, -sintheta, 0, 0,
                  sintheta,  costheta, 0, 0,
                         0,         0, 1, 0,
                         0,         0, 0, 1);
  
    return Transform{mat, glm::transpose(mat)};
  }

  [[nodiscard]] static Transform rotate_about(float theta, Vec3& axis) {
    Vec3 a = axis.normalized();
    auto radtheta = to_radians(theta);
    float s = std::sin(radtheta);
    float c = std::cos(radtheta);

    glm::mat4 mat;
    mat[0][0] = a.x() * a.x() + (1- a.x() * a.x()) * c;
    mat[0][1] = a.x() * a.y() * (1-c) - a.z() * s;
    mat[0][2] = a.x() * a.z() * (1-c) + a.y() * s;
    mat[0][3] = 0.0;

    mat[1][0] = a.x() * a.y() * (1-c) + a.z() * s;
    mat[1][1] = a.y() * a.y() + (1- a.y() * a.y()) * c;
    mat[1][2] = a.y() * a.z() * (1- c) - a.x() * s;
    mat[1][3] = 0.0;

    mat[2][0] = a.x() * a.z() * (1- c) - a.y() * s;
    mat[2][1] = a.y() * a.z() * (1- c) + a.x() * s;
    mat[2][2] = a.z() * a.z() + (1- a.z() * a.z()) * c;
    mat[2][3] = 0.0;

    mat[3][0] = 0.0;
    mat[3][1] = 0.0;
    mat[3][2] = 0.0;
    mat[3][3] = 0.0;

    return Transform{
      mat, 
      glm::transpose(mat)
    };
  }

  //look at transformation for placing a camera in the screen 
  //gives transformation between camera space n
  static Transform look_at(Vec3& pos, Vec3& look, Vec3& up) {
    auto dir = pos - look;
    auto normdir = dir.normalized();
    auto left = up.cross(normdir);
    auto normleft = left.normalized();
    auto u = normdir.cross(normleft);
    auto normu = u.normalized();

    glm::mat4 camtoworld(1.0F); 
   
    for (int i = 0; i < 3; ++i) {
      camtoworld[i][0] = -normleft[i];
      camtoworld[i][1] = normu[i];
      camtoworld[i][2] = normdir[i];
      camtoworld[i][3] = pos[i];
    }

    return Transform{camtoworld, glm::inverse(camtoworld)};
  }


  Vec3 operator()(const Vec3& point) const {
    float x = point.x();
    float y = point.y();
    float z = point.z();
  
    float xp = m_[0][0]*x + m_[0][1]*y + m_[0][2]*z; 
    float yp = m_[1][0]*x + m_[1][1]*y + m_[1][2]*z; 
    float zp = m_[2][0]*x + m_[2][1]*y + m_[2][2]*z; 
    
    return Vec3{xp, yp, zp};
  }

  Ray operator()(const Ray &ray) const {
    auto res = ray;
    res.point1_ = (*this)(ray.point1_);//apply transformation to point
    res.point2_ = (*this)(ray.point2_);
    res.lab_ = (*this)(ray.lab_); //apply transformation to vector
    return res;
  }
  
  //composing transformations
  Transform operator*(const Transform& t2) const {
    return Transform{
      m_ * t2.m_,
      t2.minv_ * minv_ 
    };
  }

  [[nodiscard]] bool swap_handedness() const {
    float det =
        m_[0][0] * (m_[1][1] * m_[2][2] - m_[1][2] * m_[2][1]) -
        m_[0][1] * (m_[1][0] * m_[2][2] - m_[1][2] * m_[2][0]) +
        m_[0][2] * (m_[1][0] * m_[2][1] - m_[1][1] * m_[2][0]);
    return det < 0;
  }

  
};



#endif
