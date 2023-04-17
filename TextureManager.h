#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<string>
#include<map>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	static SDL_Texture* loadTexture(std::string file);
	static SDL_Texture* textTexture(std::string sentence, SDL_Color color = { 255,255,0 });

private:

};


#endif // !TEXTURE_MANAGER
