#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <SDL2/SDL.h>
#include <memory>

#include "image.hpp"
#include "camera.hpp"
#include "pointlight.hpp"
#include "sphere.hpp"


class Scene {
  public: 
    Scene();
    bool render(Image& image);

    Camera cam;
    //list of objects in the screen
    std::vector<std::shared_ptr<AbstractObject>> objects;

    std::vector<std::shared_ptr<AbstractLight>> lights;

};




#endif
