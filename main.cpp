#include"GameSystem.h"
#include"Menu.h"

using namespace std;

GameSystem *game = new GameSystem();

Menu* menuStart, *menuGameOver;

const int TARGET_FPS = 120;
constexpr float FRAME_TIME = 1000.0f / TARGET_FPS;

int main(int argc, char * argv[]) {
	srand(time(NULL));

	game->Init("OctopusRun", GAME_WIDTH, GAME_HEIGHT, 0);

	while (game->Running()) {
		Uint32 frameStart = SDL_GetTicks();

		if (game->Menu()) {
			if (!menuStart) {
				menuStart = new Menu(
					{
					{0,"New Game"},
					{1,"Exit"}
					},
					"assets/background/background1.png",
					"OCTOPUS RUN"
				);
			}
			int a = menuStart->ShowMenu("fonts/DS-DIGI.TTF");

			switch (a) {
			case 0:
				game->inChange(0, 1, 0);
				if (menuStart) {
					delete menuStart;
					menuStart = nullptr;
				}
				break;
			case 1:
				game->inChange(0, 0, 0);
				break;
			}
		}

		if (!game->GameOver() and !game->Menu()) {
			game->Handle_event();
			game->update();
			game->Render();
		}

		if (game->GameOver()) {
			Mix_HaltMusic();
			if (!menuGameOver) {
				menuGameOver = new Menu(
					{
					{0,"Play Again"},
					{1,"Exit"},
					},
					"assets/background/background2.png",
					"GAME OVER"
				);
				
			}

			string tmp = "HIGH SCORE : " + to_string(game->getHighScore());
			menuGameOver->changeSentence(tmp.c_str());

			int a = menuGameOver->ShowMenu("fonts/DS-DIGI.TTF");
			switch (a) {
			case 0:
				game->play_again();
				game->inChange(0, 1, 0);
				if (menuGameOver) {
					delete menuGameOver;
					menuGameOver = nullptr;
				}
				break;
			case 1:
				game->inChange(0, 0, 0);
				break;
			default:
				break;
			}
		}

		Uint32 frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < FRAME_TIME) {
			SDL_Delay(FRAME_TIME - frameTime);
		}
	}

	game->clear();

	return 0;
}