#ifndef IMAGE_HPP 
#define IMAGE_HPP 

#include <string>
#include <vector>
#include <SDL2/SDL.h>

struct RGB {
  double red;
  double blue;
  double green;
};

struct PixelCoordinate {
  int x;
  int y;
};


class Image {
  public:
    Image();//
    ~Image();//

    void initialize(const int _xsize, const int _ysize, SDL_Renderer *_renderer);//

    void setpixel(const int x, const int y, const int red, const int green, const int blue);

    void display();//

  private:
		Uint32 convert_color(const double red, const double green, const double blue);

    void init_texture();//

  public:
    //arrays to store image data
    std::vector<std::vector<double>> redchannel;
    std::vector<std::vector<double>> greenchannel;
    std::vector<std::vector<double>> bluechannel;

    //store the dimension of the image
    
    int xsize;
    int ysize;

    //SDL stuff
    SDL_Renderer* renderer;
    SDL_Texture* texture;

};




#endif
