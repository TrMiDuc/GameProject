#include "Animation.h"
#include"TextureManager.h"

Animation::Animation(const char* path, int IMG_value)
{
    FilePath = path;
    NumberOfImg = IMG_value;

    for (int i = 0; i < NumberOfImg; i++) {
        std::string a = path + std::to_string(i + 1) + ".png";
        texture.push_back(TextureManager::loadTexture(a.c_str()));
    }
}

    SDL_Texture *Animation::getTex()
    {
        cnt++;
        if (cnt >= NumberOfImg * FrameRate) cnt = 0;
        int i = cnt / FrameRate;

        return texture[i];
    }
