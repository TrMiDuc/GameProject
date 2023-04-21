#ifndef OBJECT_H
#define OBJECT_H

#include<SDL.h>
#include<stdlib.h>
#include<string>
#include<deque>
#include<iostream>
#include"Struct.h"

#define GAME_HEIGHT 640
#define GAME_WIDTH 480

class Object
{
public:
	Object(const char* path, SDL_Rect Nsrc = {0,0,0,0});
	Object(std::string line, SDL_Color color = {255,255,0});
	~Object() {};

	virtual void Render(); //render object
	virtual void setObjTex(SDL_Texture* tex);
	
	virtual SDL_Rect getObjectLocation() { return des; }
	virtual void setDesRect(SDL_Rect a) { des = a; }

protected:
	SDL_Rect src, des;
	SDL_Texture* ObjTexture;
};

class Player : public Object
{
public:
	Player(std::string line, SDL_Rect Nsrc);
	~Player() {};

	void goUp();
	void goDown();
	void setDefaultPos() { des = { GAME_WIDTH / 2, GAME_HEIGHT / 2, 40, 35 }; }

	bool Stop() { return isStop; }
	void Move() { isStop = false; }
	void UnMove() { isStop = true; }

private:
	int DownSpeed;
	const int UpSpeed = 40;

	int timeT = 0;

	bool isStop = true;
};

class Obstacle
{
public:
	Obstacle(std::deque<std::string> line);
	~Obstacle() {};

	void RunBack(Triple_Rect &rect);
	void TripleRender(Triple_Rect &rect);
	Triple_Rect RandomRect(int size, int distan,int index);
	bool Stop() { return isStop; }
	void Move(bool a) { isStop = a; }
private:

	int speed = 1;
	Triple_Rect rect;
	SDL_Texture* ObstacleTex[3];

	bool isStop = true;
};

#endif // !OBJECT_H