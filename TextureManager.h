#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<string>


class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	static SDL_Texture* loadTexture(std::string file); //get the path to image, return texture
	static SDL_Texture* textTexture(std::string sentence, SDL_Color color = { 255,255,0 }); //get the words, return texture

private:
};


#endif // !TEXTURE_MANAGER
