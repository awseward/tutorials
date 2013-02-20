#include "dot.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <unistd.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

using namespace std;

vector<Dot> dots;
vector<SDL_Surface*> surfaces;

/*
  
  SDL STUFF

 */

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const int SCREEN_BPP = 32;

SDL_Surface* background = NULL;
SDL_Surface* screen = NULL;

SDL_Event event;

TTF_Font *font = NULL;

SDL_Color textColor = { 0, 0, 0 };

SDL_Surface *load_image( std::string filename ) {
  SDL_Surface* loaded = NULL;
  SDL_Surface* optimized = NULL;

  loaded = IMG_Load( filename.c_str() );
  if( loaded != NULL ) {
    optimized = SDL_DisplayFormat( loaded );
    SDL_FreeSurface( loaded );
    if( optimized != NULL )
      SDL_SetColorKey( optimized, SDL_SRCCOLORKEY, SDL_MapRGB( optimized->format, 0, 0xFF, 0xFF ) );
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

  SDL_WM_SetCaption( "aoisudghaoiweaiohagwe", NULL );
  return true;
}

bool load_files() {
  background = load_image( "background.png" );
  font = TTF_OpenFont( "lazy.ttf", 20 );

  if( background == NULL || font == NULL )
    return false;
  return true;
}

void clean_up() {
  SDL_FreeSurface( background );
  TTF_CloseFont( font );
  TTF_Quit();
  SDL_Quit();
}

/*

  END OF SDL STUFF
  
 */

int main() {
  srand(time(NULL));
  // create some dots
  for(unsigned int i = 0; i < 10000; i++) {
    dots.push_back(Dot(50, 50, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT));
  }
  // display all the dots...
  for (unsigned int i = 0; i < dots.size(); i++) {
    cout << dots[i].to_s() << endl;
  }

  bool quit = false;
  if( init() == false )
    return 1;
  if( load_files() == false )
    return 1;

  // generate text surface of each name...?
  for(unsigned int i = 0; i < dots.size(); i++) {
    surfaces.push_back(TTF_RenderText_Solid( font, dots[i].get_name().c_str(), textColor ));
  }

  while( quit == false ) {
    apply_surface( 0, 0, background, screen );
    for(unsigned int i = 0; i < dots.size(); i++) {
      apply_surface( dots[i].get_x(), dots[i].get_y(), surfaces[i], screen);
      if( SDL_Flip( screen ) == -1 )
	return 1;
    }
    quit = true;
  }
  
  sleep(3);
  return 0;
}
