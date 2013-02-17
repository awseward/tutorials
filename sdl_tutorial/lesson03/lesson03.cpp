#include "SDL/SDL_image.h"

SDL_Surface *load_image( std::string filename ) {
  SDL_Surface* loaded = NULL;
  SDL_Surface* optimized = NULL;
  loaded = IMG_Load( filename.c_str() );
  if( loaded != NULL ) {
    optimized = SDL_DisplayFormat( loaded );
    SDL_FreeSurface( loaded );
  }
  return optimized;
}

// same as lesson02...
