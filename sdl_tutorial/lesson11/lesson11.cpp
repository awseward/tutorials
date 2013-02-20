#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;

SDL_Event event;

TTF_Font *font = NULL;

SDL_Color textColor = { 0, 0, 0 };

Mix_Music *music = NULL;

Mix_Chunk *scratch = NULL;
Mix_Chunk *high = NULL;
Mix_Chunk *med = NULL;
Mix_Chunk *low = NULL;

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

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* dest, SDL_Rect* clip = NULL )
{
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
  if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    return false;
  SDL_WM_SetCaption( "Monitor Music", NULL );
  return true;
}

bool load_files() {
  background = load_image( "background.png" );
  font = TTF_OpenFont( "lazy.ttf" , 30 );
  if( background == NULL || font == NULL )
    return false;
  music = Mix_LoadMUS( "beat.wav" );
  if( music == NULL )
    return false;

  scratch = Mix_LoadWAV( "scratch.wav" );
  high = Mix_LoadWAV( "high.wav" );
  med = Mix_LoadWAV( "low.wav" );
  low = Mix_LoadWAV( "low.wav" );

  if( ( scratch == NULL ) ||
      ( high == NULL ) ||
      ( med == NULL ) ||
      ( low == NULL ) )
    return false;
  return true;
}

void clean_up() {
  SDL_FreeSurface( background );
  
  Mix_FreeChunk( scratch );
  Mix_FreeChunk( high );
  Mix_FreeChunk( med );
  Mix_FreeChunk( low );

  Mix_FreeMusic( music );
  TTF_CloseFont( font );
  Mix_CloseAudio();
  TTF_Quit();
  SDL_Quit();
}

int main( int argc, char* args[] ) {
  bool quit = false;
  if( init() == false )
    return 1;
  if( load_files() == false )
    return 1;

  apply_surface( 0, 0, background, screen );
  
  message = TTF_RenderText_Solid( font, "1, 2, 3, 4 bro!", textColor );
  if( message == NULL )
    return 1;
  apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 100, message, screen );
  SDL_FreeSurface( message );
  
  message == TTF_RenderText_Solid( font, "Press 9 to play/pause bro!", textColor );
  if( message == NULL )
    return 1;
  apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 200, message, screen );
  SDL_FreeSurface( message );

  message = TTF_RenderText_Solid( font, "Press 0 to stop, bro!", textColor );
  if( message == NULL )
    return 1;
  apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 300, message, screen );
  SDL_FreeSurface( message );

  if( SDL_Flip( screen ) == -1 )
    return 1;
  
  while( quit == false ) {
    while( SDL_PollEvent( &event ) ) {
      if( event.type == SDL_KEYDOWN ) {
	if( event.key.keysym.sym == SDLK_1 ) {
	  if( Mix_PlayChannel ( -1, scratch, 0 ) == -1 )
	    return 1;
	}
	else if( event.key.keysym.sym == SDLK_2 ) {
	  if( Mix_PlayChannel ( -1, high, 0 ) == -1 )
	    return 1;
	}
	else if( event.key.keysym.sym == SDLK_3 ) {
	  if( Mix_PlayChannel( -1, med, 0 ) == -1 )
	    return 1;
	}
	else if( event.key.keysym.sym == SDLK_4 ) {
	  if( Mix_PlayChannel( -1, low, 0 ) == -1 )
	    return 1;
	}
	else if( event.key.keysym.sym == SDLK_9 ) {
	  if( Mix_PlayingMusic() == 0 ) {
	    if( Mix_PlayMusic( music, -1 ) == -1 )
	      return 1;
	  }
	  else {
	    if( Mix_PausedMusic() == 1 )
	      Mix_ResumeMusic();
	    else
	      Mix_PauseMusic();
	  }
	}
	else if( event.key.keysym.sym == SDLK_0 ) {
	  Mix_HaltMusic();
	}
      }
      if( event.type == SDL_QUIT )
	quit == true;
    }
  }
  
  clean_up();
  return 0;
}
