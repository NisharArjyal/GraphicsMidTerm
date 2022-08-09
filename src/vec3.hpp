#ifndef VEC3_HPP
#define VEC3_HPP

class  Vec3 {
  public:
//members
  double x_;
  double y_;
  double z_;

//methods
 public:
  Vec3() : x_{0}, y_{0}, z_{0} {} //default constructor

  Vec3(double x_f, double y_f, double z_f) : x_{x_f}, y_{y_f}, z_{z_f} {} // constructor
  
  // constexpr explicit Vec3(const Normal3& normal) noexcept;
  // constexpr explicit Vec3(const Point3& point) noexcept;

  double x() const noexcept { return x_; }

  double y() const noexcept { return y_; }

  double z() const noexcept{ return z_; }

  double& x() noexcept { return x_; }

  double& y() noexcept { return y_; }

  double& z() noexcept{ return z_; }

  Vec3 operator-() const noexcept { return Vec3 {-x_, -y_, -z_}; }

  double operator[](int idx) const;

  double& operator[](int idx);

  Vec3& operator+=(const Vec3& vec) noexcept;

  Vec3& operator-=(const Vec3& vec) noexcept;

  Vec3& operator*=(const Vec3& vec) noexcept;

  Vec3 operator/=(const double& denom);

  Vec3 operator+(const Vec3& vec) const noexcept;

  Vec3 operator-(const Vec3& vec) const noexcept;

  double dot(const Vec3& vec) const;
  
  double squared_l2_norm();

  double norm();

  void normalize(); //mutably normalize
                    
  Vec3 normalized();

  Vec3 operator*=(double scalar);

  Vec3 operator*(double scalar);
  
  Vec3 operator/(double scalar);

  Vec3 operator/(const Vec3& denom);

  Vec3 abs();

  bool hasNaNs() const noexcept;

  Vec3 cross(const Vec3& vec);
};

Vec3 operator*(double scalar, const Vec3& vec);

#endif

