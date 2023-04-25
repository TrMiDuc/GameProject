#include "GameSystem.h"
#include"Object.h"
#include"Collision.h"
#include"Animation.h"
#include"Struct.h"

#define max_Ob 4

GameSystem::GameSystem() {}

GameSystem::~GameSystem(){}

SDL_Renderer *GameSystem::renderer;
Mix_Music* GameSystem::music;

std::deque<Triple_Rect> save;

Object* ground1, *ground2, * background, * G_point;
Player* player;
Obstacle* obstacle;

Mix_Chunk* goUpSound, *GetOverSound, * colliSound;

Animation* playerAni;

void GameSystem::Init(const char* name, int width, int height, bool fullscreen)
{
	if (SDL_INIT_VIDEO < 0) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		isRunning = false;
	}
	else {
		//init audio
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
			printf("Unable to initialize audio: %s\n", Mix_GetError());
			isRunning = false;
		}

		//init ttf
		if (TTF_Init() < 0) {
			printf("TTF_Init: %s\n", TTF_GetError());
		}
		font = TTF_OpenFont("fonts/DS-DIGI.TTF", 26);

		//init window
		Uint32 flags = SDL_WINDOW_SHOWN;
		if (fullscreen == true) flags = SDL_WINDOW_FULLSCREEN;
		window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
		if (!window) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			isRunning = false;
		}

		//init renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (!renderer) {
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			isRunning = false;
		}

		//init Object ground
		ground1 = new Object("assets/ground/seabed1.png",{0,0,0,0});
		ground1->setDesRect({ 0, GAME_HEIGHT*7/8, GAME_WIDTH, GAME_HEIGHT/8 });
		ground2 = new Object("assets/ground/seabed1.png", { 0,0,0,0 });
		ground2->setDesRect({ GAME_WIDTH, GAME_HEIGHT * 7 / 8, GAME_WIDTH, GAME_HEIGHT / 8 });

		//init Object background
		background = new Object("assets/background/background4.png",{0,0,0,0});
		background->setDesRect({ 0, 0, GAME_WIDTH, GAME_HEIGHT });

		//init Obstacles Ob
		std::deque<std::string> Ob = {
			"assets/Obstacles/Obstacles1.png",
			"assets/Obstacles/Obstacles2.png",
			"assets/Obstacles/Obstacles3.png"
		};
		obstacle = new Obstacle(Ob);

		//Setup player animation and init Player
		playerAni = new Animation("assets/octopus/", 10);

		player = new Player("assets/octopus/1.png", { 110,100,82,85 });
		player->setDefaultPos();

		//set BGM
		music = Mix_LoadMUS("sounds/BGM.wav");
		if (!music) {
			printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
			exit(1);
		}

		//set sound effect
		goUpSound = Mix_LoadWAV("sounds/octopus_swim.wav");
		GetOverSound = Mix_LoadWAV("sounds/ObstacleOver.wav");
		colliSound = Mix_LoadWAV("sounds/gethit.ogg");

		//running game
		isRunning = true;
	}
}

void GameSystem::update()
{
	SDL_Rect playerRe = player->getObjectLocation();// get player current position

	//Change the game background and ground when reach the set point
	static bool IMGload = true;
	if (point == 40 and IMGload) {
		background->setObjTex(IMG_LoadTexture(renderer, "assets/background/background3.png"));
		ground1->setObjTex(IMG_LoadTexture(renderer, "assets/ground/seabed2.png"));
		ground2->setObjTex(IMG_LoadTexture(renderer, "assets/ground/seabed2.png"));
		IMGload = false;
	}

	//Setup player to render
	if (!player->Stop()) {
		player->setObjTex(playerAni->getTex());
	}
	//gravity
	player->goDown();


	//ground movement
	ground1->MoveBack();
	ground2->MoveBack();
	if (ground1->getObjectLocation().x + ground1->getObjectLocation().w <= 0) {
		ground1->setDesRect({ GAME_WIDTH, GAME_HEIGHT * 7 / 8, GAME_WIDTH, GAME_HEIGHT / 8 });
	}
	if (ground2->getObjectLocation().x + ground2->getObjectLocation().w <= 0) {
		ground2->setDesRect({ GAME_WIDTH, GAME_HEIGHT * 7 / 8, GAME_WIDTH, GAME_HEIGHT / 8 });
	}

	//Setup Obstacles to render
	while (save.size() < max_Ob) {
		Triple_Rect a = obstacle->RandomRect(max_Ob, GAME_WIDTH / 2, save.size());
		save.push_back(a);
	}
	if (save[0].on.x + save[0].on.w < 0) save.pop_front();
	while (save.size() < max_Ob) {
		Triple_Rect a = obstacle->RandomRect(max_Ob, GAME_WIDTH / 2, save.size() - 1);
		save.push_back(a);
	}

	//Obstacles move
	if (!player->Stop()) {
		for (int i = 0; i < max_Ob; i++) obstacle->RunBack(save[i]);
	}

	//Check if collision
	if (SDL_HasIntersection(&playerRe, &roof)) {
		Mix_PlayChannel(3, colliSound, 0);
		isGameOver = true; IMGload = true;
	}
	if (SDL_HasIntersection(&playerRe, &groundRe)) {
		Mix_PlayChannel(3, colliSound, 0);
		isGameOver = true; IMGload = true;
	}
	for (int i = 0; i < max_Ob; i++) {
		if (Rect_colli(playerRe, save[i])) {
			Mix_PlayChannel(3, colliSound, 0);
			isGameOver = true; IMGload = true;
		}
	}

	//point get and update point to render
	if (stepOver(playerRe, save[0].on)) {
		Mix_Volume(-1, 32);
		Mix_PlayChannel(-1, GetOverSound, 0);
		point++;
		TakeHigher();
	}

	delete G_point;   //release previous point
	G_point = new Object(std::to_string(getScore()));
	G_point->setDesRect({ GAME_WIDTH / 2 - 25,50,50,70 });

	//playing BGM
	if (!isMenu) {
		if (Mix_PlayingMusic() == 0) {
			Mix_PlayMusic(music, -1);
		}
	}
}

void GameSystem::Handle_event()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	const unsigned char* KeyboardState = SDL_GetKeyboardState(nullptr); //check what key is press

	switch (event.type) {
	case SDL_QUIT:                //if quit the game
		isRunning = false;
		break;
	
	case SDL_KEYDOWN:             //check the key
		if (KeyboardState[SDL_SCANCODE_SPACE]) {
			player->goUp();
			Mix_Volume(0, 10);
			Mix_PlayChannel(0, goUpSound, 0);
		}
		if (KeyboardState[SDL_SCANCODE_LSHIFT] and KeyboardState[SDL_SCANCODE_RETURN]) play_again();
		break;
	}
}

void GameSystem::Render()
{
	SDL_RenderClear(renderer);

	background->Render(); //Render background
	
	//Render Obstacles
	for (int i = 0; i < max_Ob; i++) {
		obstacle->TripleRender(save[i]);
	}

	G_point->Render(); 	//Render point

	//Render ground
	ground1->Render(); 	
	ground2->Render();

	player->Render(); 	//Render player

	SDL_RenderPresent(renderer);
}

void GameSystem::play_again()
{
	point = 0;
	save.clear();

	Mix_RewindMusic();

	player = new Player("assets/octopus/1.png", { 110,100,82,85 });
	player->setDefaultPos();
	player->UnMove();

	background->setObjTex(IMG_LoadTexture(renderer, "assets/background/background4.png"));
	ground1->setObjTex(IMG_LoadTexture(renderer, "assets/ground/seabed1.png"));
	ground2->setObjTex(IMG_LoadTexture(renderer, "assets/ground/seabed1.png"));

	SDL_RenderClear(renderer);

	isGameOver = false;
}

void GameSystem::clear()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_HaltChannel(-1);
	TTF_CloseFont(font);

	std::cout << "Game clear!";
	SDL_Quit();
}

void GameSystem::inChange(bool Menu, bool Running, bool GameOver)
{
	isMenu = Menu;
	isRunning = Running;
	isGameOver = GameOver;
}
