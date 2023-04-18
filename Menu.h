#pragma once

#define Max_set 4
#define GAME_WIDTH 480
#define GAME_HEIGHT 640

#include<SDL.h>
#include<string>
#include<vector>
#include<SDL_ttf.h>
#include<map>


class Menu {
public:
	Menu(std::map<int, std::string> Option, std::string name = "Octopus Run");
	~Menu() {};

	int ShowMenu(const char* file);
	void changeSentence(const char* sentence) { MenuSentence = sentence; }
	void printOnMenu();
	void setMenuFont(const char* file);
	void setMenuBackground(SDL_Texture* Background) { MenuBackground = Background; }

protected:
	std::map <int, std::string> Setting;
	std::vector<SDL_Texture*> TextTexture;
	std::vector<SDL_Rect> SettingRect;

	std::string MenuSentence;

	SDL_Rect GameName = {GAME_WIDTH/4,50,GAME_WIDTH/2,150};

	SDL_Texture* MenuBackground;
	SDL_Texture* NameTex;

	TTF_Font* font;
};

