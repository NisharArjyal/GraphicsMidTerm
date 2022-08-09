#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP


#define _USE_MATH_DEFINES
#include <cmath>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>


#include "vec3.hpp"
#include "ray.hpp"

constexpr bool FWDTFORM = true;
constexpr bool BCKTFORM = false;

class Transform
{
	public:
		// Constructor & destructor.
		Transform();
		~Transform();
		
		// Construct from a pair of matrices.
		Transform(const glm::mat4 &fwd, const glm::mat4 &bck);
		Transform inverse() const;
		
		// Function to set translation, rotation and scale components.
		void set_transform(const Vec3 &translation,
					const Vec3 &rotation,
					const Vec3 &scale);
												
		// Functions to return the transform matrices.
    glm::mat4 get_forward();
		glm::mat4 get_backward();
		
		// Function to apply the transform.
		Ray apply(const Ray& inputRay, bool dirFlag);
		Vec3 apply(const Vec3 &inputVector, bool dirFlag);
		
		// Overload operators.
		friend Transform operator* (const Transform &lhs, const Transform &rhs);
		
		// Overload the assignment operator.
		Transform operator= (const Transform &rhs);
		
		
	private:
    glm::mat4 m_; 
		glm::mat4 minv_;
};




#endif
