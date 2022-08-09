#include <memory>

#include "image.hpp"



Image::Image() {
  xsize = 0;
  ysize = 0;
  texture = NULL;
}

Image::~Image() {
  if (texture != NULL) {
    SDL_DestroyTexture(texture);
  }
}

void Image::initialize(const int _xsize, const int _ysize, SDL_Renderer *_renderer) {

  //resize image arrays
  redchannel.resize(_xsize, std::vector<double>(_ysize, 0));
  greenchannel.resize(_xsize, std::vector<double>(_ysize, 0));
  bluechannel.resize(_xsize, std::vector<double>(_ysize, 0));

  //store dimension
  
  xsize = _xsize;
  ysize = _ysize;

  renderer = _renderer;
  //initialize the texture
  init_texture();

}

void Image::setpixel(const int x, const int y, const int red, const int green, const int blue) {
  redchannel.at(x).at(y) = red;
  greenchannel.at(x).at(y) = green;
  bluechannel.at(x).at(y) = blue;
}

void Image::display() {
  //allocate memory for a pixel buffer
  Uint32 *tempPixels = new Uint32[xsize * ysize];

  //clear the pixel buffer
  memset(tempPixels, 0, xsize * ysize * sizeof(Uint32));

  for (int x = 0; x < xsize; ++x) {
    for (int y = 0; y < ysize; ++y) {
			tempPixels[(y*xsize)+x] = convert_color(redchannel.at(x).at(y), greenchannel.at(x).at(y), bluechannel.at(x).at(y));
    }
  }
  //update the texture with the pixel buffer
  
  SDL_UpdateTexture(texture, NULL, tempPixels, xsize*sizeof(Uint32));
  //delete the pixel buffer

  delete[] tempPixels;

  //copy the texture to the renderer
  SDL_Rect srcrect, bounds;

  srcrect.x = 0;
  srcrect.y = 0;

  srcrect.w = xsize;
  srcrect.h = ysize;
  bounds = srcrect;
  SDL_RenderCopy(renderer, texture, &srcrect, &bounds);
}

void Image::init_texture() {
  //initialize the texture
  Uint32 rmask, gmask, bmask, amask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
	#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
	#endif


  //delete any previously created texture

  if (texture != NULL) {
    SDL_DestroyTexture(texture);
  }

  SDL_Surface *tempsurface = SDL_CreateRGBSurface(0, xsize, ysize, 32, rmask, gmask, bmask, amask);
  texture = SDL_CreateTextureFromSurface(renderer, tempsurface);
  SDL_FreeSurface(tempsurface);
}

//function to convert color to Uint32
Uint32 Image::convert_color(const double red, const double green, const double blue) {
  unsigned char r = static_cast<unsigned char>(red);
  unsigned char g = static_cast<unsigned char>(green);
  unsigned char b = static_cast<unsigned char>(blue);
  
  #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 pixelcolor = (r << 24) + (g << 16) + (b << 8) + 255;
  #else
    Uint32 pixelcolor = (255 << 24) + (b << 16) + (g << 8) + r;
  #endif
  
  return pixelcolor;
}








