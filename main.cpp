#include"GameSystem.h"
#include"Menu.h"

using namespace std;

GameSystem *game = new GameSystem();

Menu* menu;

const int TARGET_FPS = 120;
constexpr float FRAME_TIME = 1000.0f / TARGET_FPS;

int main(int argc, char * argv[]) {
	srand(time(NULL));

	game->Init("OctopusRun", GAME_WIDTH, GAME_HEIGHT, 0);

	while (game->Running()) {
		Uint32 frameStart = SDL_GetTicks();

		if (game->Menu()) {
			if (!menu) {
				menu = new Menu(
					{
					{0,"New Game"},
					{1,"Exit"},
					{2,"Tutorial"}
					}
				);
			}
			int a = menu->ShowMenu("fonts/Vnarialb.ttf");
			game->inChange(a, 1, 0);
		}

		if (!game->GameOver() and !game->Menu()) {
			game->Handle_event();
			game->update();
			game->Render();
		}

		if (game->GameOver()) {
			game->Handle_event();
		}

		Uint32 frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < FRAME_TIME) {
			SDL_Delay(FRAME_TIME - frameTime);
		}
	}

	game->clear();

	return 0;
}