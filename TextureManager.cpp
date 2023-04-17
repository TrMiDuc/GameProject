#include "TextureManager.h"
#include"GameSystem.h"

TTF_Font* GameSystem::font = nullptr;

TextureManager::TextureManager(){}

TextureManager::~TextureManager(){}

SDL_Texture* TextureManager::loadTexture(std::string file)
{
	SDL_Surface* TemSurf = IMG_Load(file.c_str());
	if (!TemSurf) {
		printf("Surface could not be created! SDL Error: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_SetColorKey(TemSurf, true, SDL_MapRGB(TemSurf->format, 20, 45, 76));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(GameSystem::renderer, TemSurf);
	SDL_FreeSurface(TemSurf);

	if (texture == NULL) {
		printf("Texture could not be created! SDL Error: %s\n", SDL_GetError());
		exit(1);
	}
	return texture;
}

SDL_Texture* TextureManager::textTexture(std::string sentence, SDL_Color color)
{
	SDL_Surface* TemSurf = TTF_RenderText_Blended(GameSystem::font, sentence.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(GameSystem::renderer, TemSurf);
	SDL_FreeSurface(TemSurf);

	if (texture == NULL) {
		printf("Texture could not be created! SDL Error: %s\n", SDL_GetError());
		exit(1);
	}

	return texture;
}
