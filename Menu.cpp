#include "Menu.h"
#include"TextureManager.h"
#include"GameSystem.h"

bool MouseInRect(SDL_Rect& a) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if ((x >= a.x and x <= a.x + a.w) and (y >= a.y and y <= a.y + a.h)) return true;
    return false;
}

Menu::Menu(std::map<int, std::string> Option)
{
    Setting = Option;
    MenuBackground = TextureManager::loadTexture("assets/background/background1.png");
    NameTex = TextureManager::textTexture("Octopus Run", {0,0,0});
}

int Menu::ShowMenu(const char* file)
{
    setMenuFont(file);
    //setup button texture
    for (auto i : Setting) {
        TextTexture.push_back(TextureManager::textTexture(i.second, {255,0,255}));
    }

    //setup button rect
    for (int i = 0; i < Setting.size(); i++) {
        SettingRect.push_back({ 0,GAME_HEIGHT - ((int)Setting.size()- i) * 50,120,50 });
    }

    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        SDL_Quit();
        break;
    case SDL_MOUSEMOTION:
        for (int i = 0; i < Setting.size(); i++) {
            std::string tmp = Setting.at(i);
            if (MouseInRect(SettingRect[i])) TextTexture[i] = TextureManager::textTexture(tmp, {255,0,0});
            else TextTexture[i] = TextureManager::textTexture(tmp);
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        for (int i = 0; i < Setting.size(); i++) {
            if (MouseInRect(SettingRect[i]) and SDL_MOUSEBUTTONDOWN) return i;
        }
        break;
    }

    SDL_RenderClear(GameSystem::renderer);

    SDL_RenderCopy(GameSystem::renderer, MenuBackground, NULL, NULL);
    SDL_RenderCopy(GameSystem::renderer, NameTex, NULL, &GameName);

    for (int i = 0; i < Setting.size(); i++) {
        SDL_RenderCopy(GameSystem::renderer, TextTexture[i], NULL, &SettingRect[i]);
    }
    
    SDL_RenderPresent(GameSystem::renderer);
    return 4;
}

void Menu::setMenuFont(const char* file)
{
    font = TTF_OpenFont(file, 40);
}

