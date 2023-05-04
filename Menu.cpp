#include "Menu.h"
#include"TextureManager.h"
#include"GameSystem.h"

Mix_Chunk* menuEffect1, * menuEffect2;

bool MouseInRect(SDL_Rect& a) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if ((x >= a.x and x <= a.x + a.w) and (y >= a.y and y <= a.y + a.h)) return true;
    return false;
}

Menu::Menu(std::map<int, std::string> Option, const char* path, std::string name)
{
    Setting = Option;
    MenuBackground = TextureManager::loadTexture(path);
    NameTex = TextureManager::textTexture(name, {10,10,10});
    menuEffect1 = Mix_LoadWAV("sounds/menuEffect1.wav");
    menuEffect2 = Mix_LoadWAV("sounds/menuEffect2.wav");
}

Menu::~Menu(){}

int Menu::ShowMenu(const char* file)
{
    //setup button texture
    for (auto i : Setting) {
        TextTexture.push_back(TextureManager::textTexture(i.second));
    }

    //setup button rect
    for (int i = 0; i < Setting.size(); i++) {
        SettingRect.push_back({ GAME_WIDTH / 2 - 60 ,GAME_HEIGHT - ((int)Setting.size() - i) * 70,120,50 });
    }
    SDL_RenderClear(GameSystem::renderer);

    SDL_RenderCopy(GameSystem::renderer, MenuBackground, NULL, NULL);
    SDL_RenderCopy(GameSystem::renderer, NameTex, NULL, &GameName);

    printOnMenu();

    for (int i = 0; i < Setting.size(); i++) {
        SDL_RenderCopy(GameSystem::renderer, TextTexture[i], NULL, &SettingRect[i]);
    }
    
    SDL_RenderPresent(GameSystem::renderer);

    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        exit(0);
        break;
    case SDL_MOUSEMOTION:

        for (int i = 0; i < Setting.size(); i++) {
            std::string tmp = Setting.at(i);
            if (MouseInRect(SettingRect[i])) {
                Mix_Volume(1, 16);
                Mix_PlayChannel(1, menuEffect1, 0);
                TextTexture[i] = TextureManager::textTexture(tmp, { 255,0,0 });
            }
            else {
                TextTexture[i] = TextureManager::textTexture(tmp);
            }
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        for (int i = 0; i < Setting.size(); i++) {
            if (MouseInRect(SettingRect[i])) {
                Mix_Volume(2, 16);
                Mix_PlayChannel(2, menuEffect2, 0);
                return i;
            }
        }
        break;
    }

    return 4;
}



void Menu::printOnMenu()
{
    if (MenuSentence != "") {
        SDL_Texture* tmpTex = TextureManager::textTexture(MenuSentence, { 255,255,0 });
        SDL_Rect tmp = { GAME_WIDTH / 2 - 100, GAME_HEIGHT - ((int)Setting.size()+1) * 90,200,100 };
        SDL_RenderCopy(GameSystem::renderer, tmpTex, NULL, &tmp);
    }
}
