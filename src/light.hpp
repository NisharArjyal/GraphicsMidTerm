#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <memory>
#include <vector>
#include "vec3.hpp"
#include "ray.hpp"
#include "object.hpp"


class AbstractLight {
  public:
    AbstractLight(); 

    virtual ~AbstractLight();

    virtual bool compute_illumination(
        const Vec3& intpoint, 
        const Vec3& local_normal,
        const std::vector<std::shared_ptr<AbstractObject>>& objects,
        const std::shared_ptr<AbstractObject>& obj,
        Vec3& color, 
        double& intensity
        );

  public: 
    Vec3 color_;
    Vec3 location_;
    double intensity_;
};


#endif
