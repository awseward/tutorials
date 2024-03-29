#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Surface *foo = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

SDL_Event event;

SDL_Surface *load_image( std::string filename ) {
  SDL_Surface* loaded = NULL;
  SDL_Surface* optimized = NULL;
  loaded = IMG_Load( filename.c_str() );
  if( loaded != NULL ) {
    optimized = SDL_DisplayFormat( loaded );
    if( optimized != NULL ) {
      Uint32 colorkey = SDL_MapRGB( optimized->format, 0, 0xFF, 0xFF );
      SDL_SetColorKey( optimized, SDL_SRCCOLORKEY, colorkey );
    }
    SDL_FreeSurface( loaded );
  }
  return optimized;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* dest ) {
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface( source, NULL, dest, &offset );
}

bool init() {
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    return false;

  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

  if( screen == NULL )
    return false;

  SDL_WM_SetCaption( "Event test", NULL );
  return true;
}

bool load_files() {
  foo = load_image( "foo.png" );
  background = load_image( "background.png" );
  
  if( foo == NULL || background == NULL )
    return false;

  return true;
}

void clean_up() {
  SDL_FreeSurface( foo );
  SDL_FreeSurface( background );
  SDL_Quit();
}

int main( int argc, char* args[] ) {
  bool quit = false;

  if( init() == false )
    return 1;
  if( load_files() == false )
    return 1;

  apply_surface( 0, 0, background, screen );
  apply_surface( 240, 190, foo, screen );
  
  if( SDL_Flip( screen ) == -1 )
    return 1;

  while( quit == false ) {
    while( SDL_PollEvent ( &event ) ) {
      if( event.type == SDL_QUIT )
	quit = true;
    }
  }

  clean_up();
  return 0;
}
