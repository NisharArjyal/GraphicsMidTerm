#ifndef CAPP_H
#define CAPP_H

#include <SDL2/SDL.h>
#include "scene.hpp"
#include "image.hpp"
#include "camera.hpp"

class Application {
    public:
        Application();

        int  execute();
        bool init();
        void onevent(SDL_Event* event);
        void loop();
        void render();
        void exit();

        void print_vector(const Vec3& vec);


    public:
        Scene scene;
        //SDL stuff
        Image image;
        bool is_running;
        SDL_Window *window;
        SDL_Renderer *renderer;
};










#endif
