#pragma once

#include"Struct.h"
#include<SDL.h>

static bool Rect_colli(SDL_Rect& a, Triple_Rect& b)
{
	if (SDL_HasIntersection(&a, &b.on) or SDL_HasIntersection(&a, &b.under) or SDL_HasIntersection(&a, &b.mid)) {
		return true;
	}
	return false;
}

static bool stepOver(SDL_Rect& a, SDL_Rect& b) {
	if (a.x == b.x + b.w + 2) return true;
	return false;
}

