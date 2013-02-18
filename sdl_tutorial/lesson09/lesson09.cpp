#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

const int CLIP_MOUSEOVER = 0;
const int CLIP_MOUSEOUT = 1;
const int CLIP_MOUSEDOWN = 2;
const int CLIP_MOUSEUP = 3;

SDL_Surface *buttonSheet = NULL;
SDL_Surface *screen = NULL;

SDL_Event event;

SDL_Rect clips[4];

class Button {
private:
  SDL_Rect box;
  SDL_Rect* clip;

public:
  Button( int x, int y, int w, int h );

  bool contains_cursor( int x, int y );
  
  void handle_events();

  void show();
};

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
  
  SDL_WM_SetCaption( "Button Test", NULL );
  return true;
}

bool load_files() {
  buttonSheet = load_image( "button.png" );
  if( buttonSheet == NULL )
    return false;

  return true;
}



void clean_up() {
  SDL_FreeSurface( buttonSheet );
  SDL_Quit();
}

void set_clips() {
  clips[CLIP_MOUSEOVER].x = 0;
  clips[CLIP_MOUSEOVER].y = 0;
  clips[CLIP_MOUSEOVER].w = 320;
  clips[CLIP_MOUSEOVER].h = 240;

  clips[CLIP_MOUSEOUT].x = 320;
  clips[CLIP_MOUSEOUT].y = 0;
  clips[CLIP_MOUSEOUT].w = 320;
  clips[CLIP_MOUSEOUT].h = 240;

  clips[CLIP_MOUSEDOWN].x = 0;
  clips[CLIP_MOUSEDOWN].y = 240;
  clips[CLIP_MOUSEDOWN].w = 320;
  clips[CLIP_MOUSEDOWN].h = 240;

  clips[CLIP_MOUSEUP].x = 320;
  clips[CLIP_MOUSEUP].y = 240;
  clips[CLIP_MOUSEUP].w = 320;
  clips[CLIP_MOUSEUP].h = 240;
}

Button::Button( int x, int y, int w, int h ) {
  box.x = x;
  box.y = y;
  box.w = w;
  box.h = h;
  clip = &clips[CLIP_MOUSEOUT];
}

bool Button::contains_cursor( int x, int y ) {
  if( ( x > box.x ) &&
      ( x < box.x + box.w ) &&
      ( y > box.y ) &&
      ( y < box.y + box.h ) ) {
    return true;
  }
  return false;
}

void Button::handle_events() {
  int x = 0, y = 0;

  if( event.type == SDL_MOUSEMOTION ) {
    x = event.motion.x;
    y = event.motion.y;
    
    if( contains_cursor( x, y ) )
      clip = &clips[CLIP_MOUSEOVER];
    else
      clip = &clips[CLIP_MOUSEOUT];
  }
  if( event.type ==SDL_MOUSEBUTTONDOWN ) {
    if( event.button.button == SDL_BUTTON_LEFT ) {
      x = event.button.x;
      y = event.button.y;
      
      if( contains_cursor( x, y ) )
	clip = &clips[CLIP_MOUSEDOWN];
    }
  }
  if( event.type == SDL_MOUSEBUTTONUP ) {
    if( event.button.button == SDL_BUTTON_LEFT ) {
      x = event.button.x;
      y = event.button.y;

      if( contains_cursor( x, y ) )
	clip = &clips[CLIP_MOUSEUP];
    }
  }
}

void Button::show() {
  apply_surface( box.x, box.y, buttonSheet, screen, clip );
}

int main( int argc, char* args[] ) {
  bool quit = false;
  
  if( init() == false )
    return 1;

  if( load_files() == false )
    return 1;

  set_clips();

  Button myButton( 170, 120, 320, 240 );

  while( quit == false ) {
    if( SDL_PollEvent( &event ) ) {
      myButton.handle_events();
      
      if( event.type == SDL_QUIT )
	quit = true;
    }

    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF) );

    myButton.show();

    if( SDL_Flip( screen ) == -1 )
      return 1;
  }

  clean_up();
  return 0;
}
