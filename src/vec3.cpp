#include <cassert>
#include <cmath>

#include "vec3.hpp"


double Vec3::operator[](int idx) const { 
  assert(idx < static_cast<int>(3) && idx >= static_cast<int>(0));
  return idx == 0 ?  x_ 
                  : idx == 1 ? y_
                  : z_;
}


double& Vec3::operator[](int idx) { 
  assert(idx < static_cast<int>(3) && idx >= static_cast<int>(0));
  return idx == 0 ?  x_
                  : idx == 1 ? y_
                  : z_;
}

Vec3& Vec3::operator+=(const Vec3& vec) noexcept {
  x_ += vec.x();
  y_ += vec.y();
  z_ += vec.z();
  return *this;
}


Vec3& Vec3::operator-=(const Vec3& vec) noexcept {
  x_ -= vec.x();
  y_ -= vec.y();
  z_ -= vec.z();
  return *this;
}

Vec3& Vec3::operator*=(const Vec3& vec) noexcept {
  x_ *= vec.x();
  y_ *= vec.y();
  z_ *= vec.z();
  return *this;
}

Vec3 Vec3::operator/=(const double& denom) {
  assert(denom != 0);
  return (*this) *= static_cast<double>(1/denom);
}

Vec3 Vec3::operator+(const Vec3& vec) const noexcept {
  return Vec3 {x_ + vec.x_, y_ + vec.y_, z_ + vec.z_};
}

Vec3 Vec3::operator-(const Vec3& vec) const noexcept {
  return Vec3 {x_ - vec.x_, y_ - vec.y_, z_ - vec.z_};
}


double Vec3::dot(const Vec3& vec) const {
  return x_ * vec.x_ + y_ * vec.y_ + z_ * vec.z_;
}

double Vec3::squared_l2_norm() { return x_ * x_ + y_ * y_ + z_ * z_; }

double Vec3::norm() { return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_); }

Vec3 Vec3::operator*=(double scalar) {
  this->x_ *= scalar;
  this->y_ *= scalar;
  this->z_ *= scalar;
  return *this;
}

Vec3 Vec3::operator*(double scalar) {
  auto temp = Vec3(this->x_, this->y_, this->z_);
  temp *= scalar;
  return temp;
}

Vec3 operator*(double scalar, const Vec3& vec) {
  auto temp = Vec3{vec.x_, vec.y_, vec.z_};
  temp *= scalar;
  return temp;
}

Vec3 Vec3::operator/(double scalar) {
  auto temp = Vec3(this->x_, this->y_, this->z_);
  temp *= static_cast<double>(1)/scalar;
  return temp;
}

Vec3 Vec3::operator/(const Vec3& denom) {
  return Vec3 {
    x_ / denom.x_,
    y_ / denom.y_,
    z_ / denom.z_
  };
}

Vec3 Vec3::abs() {
  return Vec3{std::abs(this->x()), std::abs(this->y()), std::abs(this->z())};
}

bool Vec3::hasNaNs() const noexcept {
  return std::isnan(x_)|| std::isnan(y_) || std::isnan(z_);
}

Vec3 Vec3::cross(const Vec3& vec) {
  auto vecx = vec.x_;
  auto vecy = vec.y_;
  auto vecz = vec.z_;
  return Vec3{(y_ * vecz) - (z_ * vecy),
              (z_ * vecx) - (x_ * vecz),
              (x_ * vecy) - (y_ * vecx)
  };
}

void Vec3::normalize() { //normalizes the vector in-place
  auto vecnorm = norm();
  this->x_ *= (1.0 / vecnorm);
  this->y_ *= (1.0 / vecnorm);
  this->z_ *= (1.0 / vecnorm);
}

Vec3 Vec3::normalized() {
  Vec3 temp;
  temp.x_ = this->x_;
  temp.y_ = this->y_;
  temp.z_ = this->z_;
  auto vecnorm = this->norm();
  temp.x_ *= (1.0 / vecnorm);
  temp.y_ *= (1.0 / vecnorm);
  temp.z_ *= (1.0 / vecnorm);
  return temp;
}










