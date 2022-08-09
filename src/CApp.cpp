#include <iostream>
#include <iomanip>

#include "CApp.hpp"
#include "vec3.hpp"


Application::Application() {
  is_running = true;
  window = NULL;
  renderer = NULL;
}

bool Application::init() {

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return false;
  }

  window = SDL_CreateWindow("Ray Tracer",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      1280,
      720,
      SDL_WINDOW_SHOWN);

  if (window != NULL) {
    renderer = SDL_CreateRenderer(window, -1, 0);
    //initialize the Image
    
    image.initialize(1280, 720, renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    scene.render(image);
    image.display();

    SDL_RenderPresent(renderer);

    //create some color variation 
    // auto k = 1280.f;
    // auto l = 720.f;
    //
    // for (int i = 0; i < 1280; ++i) {
    //   for (int j = 0; j < 720; ++j) {
    //     double red = (static_cast<double>(i) / k) * 255.0;
    //     double green = (static_cast<double>(j) / l) * 255.0;
    //     image.setpixel(i, j, red, green, 0.0);
    //   }
    // }
    
    // Camera test_cam; 
    //
    // test_cam.set_position(Vec3{0.0, 0.0, 0.0});
    // test_cam.set_lookat(Vec3{0.0, 2.0, 0.0});
    // test_cam.set_up(Vec3{0.0, 0.0, 1.0});
    // test_cam.set_length(1.0);
    // test_cam.set_horizontal_size(1.0);
    // test_cam.set_aspect_ratio(1.0);
    // test_cam.update_camera_geometry();
    //
    // //get the screen center and U, V vector for display
    // 
    // auto screen_center = test_cam.get_screen_center(); 
    // auto screenU = test_cam.get_u(); 
    // auto screenV = test_cam.get_v(); 
    //
    // std::cout << "Camera screen center: \n";
    // print_vector(screen_center);
    // std::cout << "Camera screen U: \n";
    // print_vector(screenU);
    // std::cout << "Camera screen V: \n";
    // print_vector(screenV);

  } else {
    return false;
  }

  return true;
}

int Application::execute() {
  SDL_Event event;

  if (init() == false) {
    return -1;
  }

  while (is_running) {
    while( SDL_PollEvent(&event) != 0 )  {
      onevent(&event);
    }
    loop();
    render();
  }
  return 0;
}

void Application::onevent(SDL_Event* event) {
  if (event->type == SDL_QUIT) {
    is_running = false;
  }
}

void Application::loop() {

}

void Application::render() {
  // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  // SDL_RenderClear(renderer);
  // scene.render(image);
  // //display the image
  // image.display();
  //
  // SDL_RenderPresent(renderer);
}

void Application::exit() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  window = NULL;
  SDL_Quit();
}


void Application::print_vector(const Vec3& vec) {
  int rows = 3;

  for(int i = 0; i < 3; ++i) {
    std::cout << std::fixed << std::setprecision(3) << vec[i] << '\n';
  }
}
