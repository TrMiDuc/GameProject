#ifndef GAME_H
#define GAME_H

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<string>
#include<iostream>
#include<ctime>

#define GAME_HEIGHT 640
#define GAME_WIDTH 480

class GameSystem
{
public:
	GameSystem();
	~GameSystem();

	void Init(const char* name, int width, int height, bool fullscreen);

	void update();
	void Handle_event();
	void Render();
	void play_again();
	void clear();

	bool Running() { return isRunning; }
	bool GameOver() { return isGameOver; }
	bool Menu() { return isMenu; }

	int getScore() { return point; }
	int getHighScore() { return highscore; }

	void inChange(bool Menu = true, bool Running = false, bool GameOver = true);

	static SDL_Renderer* renderer;
	static TTF_Font* font;
	static Mix_Music* music;

private:
	bool isRunning = false;
	bool isGameOver = false;
	bool isMenu = true;

	SDL_Window* window;
	
	
	int point = 0;
	int highscore = 0;

	void TakeHigher() {
		if (point > highscore) highscore = point;
	}
};
#endif // !GAME_H
