#pragma once
#include "SDL.h"

class Entity
{
public:
    Entity();
    ~Entity();
    void SetTexture(SDL_Renderer* ren, SDL_Surface* texture);
    void SetPosition(int x, int y) { mDestinationRect.x = x; mDestinationRect.y = y; };
    void Move(int x, int y) { mDestinationRect.x += x; mDestinationRect.y += y; }
    SDL_Rect GetDestRect() { return mDestinationRect; }
    void Draw(SDL_Renderer* ren);
private:
    SDL_Rect mDestinationRect;
    SDL_Texture* mTexture = nullptr;
};