#ifndef STRUCT_H
#define STRUCT_H

#include<SDL.h>
#include<deque>

struct double_Rect {
	SDL_Rect on;
	SDL_Rect under;
};

struct Triple_Rect {
	SDL_Rect on;
	SDL_Rect mid;
	SDL_Rect under;
};



#endif // !STRUCT_H