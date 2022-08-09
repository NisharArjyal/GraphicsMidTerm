#include <vector>


#include "transform.hpp"

Transform::Transform() {
  m_ = glm::mat4(1.);
  minv_ = glm::inverse(m_);
}

Transform::~Transform() {

}

Transform::Transform(const glm::mat4 &fwd, const glm::mat4 &bck) {
  m_ = fwd;
  minv_ = bck;
}

Transform Transform::inverse() const {
  return Transform(minv_, m_);
}

void Transform::set_transform(
    const Vec3& translation, 
    const Vec3& rotation, 
    const Vec3& scale
    )
{
  //define a matrix for each component of transformation 
  glm::mat4 translation_mat {1.};
  glm::mat4 rotation_matx {1.};
  glm::mat4 rotation_maty {1.};
  glm::mat4 rotation_matz {1.};
  glm::mat4 scale_mat {1.};

  //populate with appropriate values;
  translation_mat[0][3] = translation.x_ ; 
  translation_mat[1][3] = translation.y_;
  translation_mat[2][3] = translation.z_;

	rotation_matz[0][0] =  cos(rotation.z_);
	rotation_matz[0][1] =  -sin(rotation.z_);
	rotation_matz[1][0] =  sin(rotation.z_);
	rotation_matz[1][1] =  cos(rotation.z_);

	rotation_maty[0][0] =  cos(rotation.y_);
	rotation_maty[0][2] =  sin(rotation.y_);
	rotation_maty[2][0] =  -sin(rotation.y_);
	rotation_maty[2][2] =  cos(rotation.y_);

	rotation_matx[1][1] =  cos(rotation.x_);
	rotation_matx[1][2] =  -sin(rotation.x_);
	rotation_matx[2][1] =  sin(rotation.x_);
	rotation_matx[2][2] =  cos(rotation.x_);

	scale_mat[0][0] = scale.x_;
	scale_mat[1][1] = scale.y_;
	scale_mat[2][2] = scale.z_;

  
	this->m_ =	translation_mat * 
			scale_mat *
			rotation_matx *
			rotation_maty *
			rotation_matz;
	this->minv_ = glm::inverse(m_);
}


glm::mat4 Transform::get_forward() {
  return m_;
}

glm::mat4 Transform::get_backward() {
  return minv_;
}

// Function to apply the transform.
Ray Transform::apply(const Ray &inputRay, bool dirFlag)
{
	// Create an output object.
	Ray outputRay;
	
	if (dirFlag)
	{
		// Apply the forward transform.
		outputRay.point1_ = this -> apply(inputRay.point1_, FWDTFORM);
		outputRay.point2_ = this -> apply(inputRay.point2_, FWDTFORM);
		outputRay.lab_ = outputRay.point2_ - outputRay.point1_;
	}
	else
	{
		// Apply the backward transform.
		outputRay.point1_ = this -> apply(inputRay.point1_, BCKTFORM);
		outputRay.point2_ = this -> apply(inputRay.point2_, BCKTFORM);
		outputRay.lab_ = outputRay.point2_ - outputRay.point1_;
	}
	
	return outputRay;
}


Vec3 Transform::apply(const Vec3 &inputVector, bool dirFlag) {
  float x = inputVector.x();
  float y = inputVector.y();
  float z = inputVector.z();

  float xp = m_[0][0]*x + m_[0][1]*y + m_[0][2]*z; 
  float yp = m_[1][0]*x + m_[1][1]*y + m_[1][2]*z; 
  float zp = m_[2][0]*x + m_[2][1]*y + m_[2][2]*z; 
  
  return Vec3{xp, yp, zp};
}


Transform operator*(const Transform &lhs, const Transform &rhs)
{
	// Form the product of the two forward transforms.
  glm::mat4 fwdResult = lhs.m_ * rhs.minv_;
	
	// Compute the backward transform as the inverse of the forward transform.
  glm::mat4 bckResult = glm::inverse(fwdResult);
	
	Transform finalResult (fwdResult, bckResult);
	
	return finalResult;
}

// Overload the assignment operator.
Transform Transform::operator= (const Transform &rhs)
{
// Make sure that we're not assigning to ourself.
  if (this != &rhs)
  {
	  m_ = rhs.m_;
	  minv_ = rhs.minv_;
  }

  return *this;
}

