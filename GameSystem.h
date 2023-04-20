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

	void Init(const char* name, int width, int height, bool fullscreen); //init game

	void update(); //update things in the game
	void Handle_event(); //check what event happen
	void Render(); //render things to the screen
	void play_again(); //Play Again after gameOver
	void clear(); //clear the game data after closing game

	bool Running() { return isRunning; } //check if the game is running
	bool GameOver() { return isGameOver; } //check if the game is over
	bool Menu() { return isMenu; } //check if there a Menu on

	int getScore() { return point; } //get the current point
	int getHighScore() { return highscore; } //get the highscore

	void inChange(bool Menu = true, bool Running = false, bool GameOver = true); //chang game state

	//some static variables
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

	//some default rect
	SDL_Rect roof = { 0,0,GAME_WIDTH,1 }, groundRe = { 0, GAME_HEIGHT * 15 / 16, GAME_WIDTH, GAME_HEIGHT / 16 };
};
#endif // !GAME_H
