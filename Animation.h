#pragma once
#include<SDL.h>
#include<string>
#include<vector>

class Animation {
public:
	Animation(const char* path, int IMG_value);
	~Animation() {};
	SDL_Texture *getTex();

private:
	int cnt, NumberOfImg;
	const int FrameRate = 4;
	std::string FilePath;

	std::vector<SDL_Texture*> texture;
};