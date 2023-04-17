#include "Object.h"
#include"TextureManager.h"
#include"GameSystem.h"

Object::Object(const char* path, SDL_Rect Nsrc)
{
	src = Nsrc;
	ObjTexture = TextureManager::loadTexture(path);
}

Object::Object(std::string line) {
	ObjTexture = TextureManager::textTexture(line);
}

void Object::Render()
{
	if (src.x == 0 and src.y == 0 and src.w == 0 and src.h == 0) {
		SDL_RenderCopy(GameSystem::renderer, ObjTexture, NULL, &des);
	}
	else {
		SDL_RenderCopy(GameSystem::renderer, ObjTexture, &src, &des);
	}
}

Player::Player(std::string line, SDL_Rect Nsrc): Object(line.c_str(), Nsrc)
{
	ObjTexture = TextureManager::loadTexture(line.c_str());
	src = Nsrc;
}

void Player::goUp()
{
	isStop = false;
	timeT = 0;
	des.y -= UpSpeed;
}

void Player::goDown()
{
	if (!isStop) {
		timeT++;
		DownSpeed = 1 + 3 * timeT / 120;
		des.y += DownSpeed;
	}
	else DownSpeed = 0;
}

Obstacle::Obstacle(std::deque<std::string> line)
{
	ObstacleTex[0] = TextureManager::loadTexture(line[0]);
	ObstacleTex[1] = TextureManager::loadTexture(line[1]);
	ObstacleTex[2] = TextureManager::loadTexture(line[2]);
}

void Obstacle::RunBack(Triple_Rect &rect)
{
	rect.on.x -= speed;
	rect.mid.x -= speed;
	rect.under.x -= speed;
}

void Obstacle::TripleRender(Triple_Rect &rect)
{
	SDL_RenderCopy(GameSystem::renderer, ObstacleTex[0], NULL, &rect.on);
	SDL_RenderCopy(GameSystem::renderer, ObstacleTex[1], NULL, &rect.mid);
	SDL_RenderCopy(GameSystem::renderer, ObstacleTex[2], NULL, &rect.under);
}

Triple_Rect Obstacle::RandomRect(int size, int distan, int index)
{
	

	//on
	rect.on.h = 30 + rand() % GAME_HEIGHT * 1 / 10;
	rect.on.y = 0;

	int distance = 90 + rand() % 30;
	//mid
	rect.mid.y = rect.on.h + distance;
	rect.mid.h = rect.mid.y + (30 + rand() % GAME_HEIGHT * 1 / 10);

	distance = 90 + rand() % 30;
	//under
	rect.under.y = rect.mid.y + rect.mid.h + distance;
	rect.under.h = GAME_HEIGHT - rect.under.y;


	rect.on.x = GAME_WIDTH + index * distan;
	rect.mid.x = GAME_WIDTH + index * distan;
	rect.under.x = GAME_WIDTH + index * distan;

	rect.on.w = 60;
	rect.mid.w = 60;
	rect.under.w = 60;

	return rect;
}



