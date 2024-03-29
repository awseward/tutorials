#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;

SDL_Event event;

TTF_Font *font = NULL;

SDL_Color textColor = { 255, 255, 255 };

SDL_Surface *load_image( std::string filename ) {
  SDL_Surface* loaded = NULL;
  SDL_Surface* optimized = NULL;
  loaded = IMG_Load( filename.c_str() );
  if( loaded != NULL ) {
    optimized = SDL_DisplayFormat( loaded );
    SDL_FreeSurface( loaded );
    if( optimized != NULL )
      SDL_SetColorKey( optimized, SDL_SRCCOLORKEY, SDL_MapRGB(optimized->format, 0, 0xFF, 0xFF ) );
  }
  return optimized;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* dest, SDL_Rect* clip = NULL ) {
  SDL_Rect offset;

  offset.x = x;
  offset.y = y;

  SDL_BlitSurface( source, clip, dest, &offset );
}

bool init() {
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    return false;

  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

  if( screen == NULL )
    return false;

  if( TTF_Init() == -1 )
    return false;

  SDL_WM_SetCaption( "TTF Test", NULL );

  return true;
}

bool load_files() {
  background = load_image( "background.png" );
  font = TTF_OpenFont( "lazy.ttf", 28 );

  if( background == NULL || font == NULL )
    return false;
  return true;
}

void clean_up() {
  SDL_FreeSurface( background );
  SDL_FreeSurface( message );

  TTF_CloseFont( font );
  
  TTF_Quit();
  
  SDL_Quit();
}

int main( int argc, char* args[] ) {
  bool quit = false;

  if( init() == false )
    return 1;

  if( load_files() == false )
    return 1;

  message = TTF_RenderText_Solid( font, "This shit is some goddamn text bro", textColor );

  if( message == NULL )
    return 1;

  apply_surface( 0, 0, background, screen );
  apply_surface( 0, 150, message, screen );

  if( SDL_Flip( screen ) == -1 )
    return 1;

  while( quit == false ) {
    while ( SDL_PollEvent( &event ) ) {
      if( event.type == SDL_QUIT )
	quit = true;
    }
  }

  clean_up();
  return 0;
}
