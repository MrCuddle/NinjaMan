#include "Entity.h"
Entity::Entity()
{
    mDestinationRect.x = 0;
    mDestinationRect.y = 0;
    mDestinationRect.w = 0;
    mDestinationRect.h = 0;
}

Entity::~Entity()
{
    SDL_DestroyTexture(mTexture);
}

void Entity::SetTexture(SDL_Renderer* ren, SDL_Surface* surface)
{
    mTexture = SDL_CreateTextureFromSurface(ren, surface);
    int w, h;
    SDL_QueryTexture(mTexture, nullptr, nullptr, &w, &h);
    mDestinationRect.w = w * 6;
    mDestinationRect.h = h * 6;
}

void Entity::Draw(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, mTexture, nullptr, &mDestinationRect);
}