#include <SDL.h>
#include <iostream>
int main(int argc, char *args[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    //init window, get win surface
    SDL_Window* win = SDL_CreateWindow("Hello World!", 100, 100, 320, 240, SDL_WINDOW_SHOWN);
    if (win == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    SDL_SetWindowFullscreen(win, SDL_WINDOW_INPUT_FOCUS);

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_Texture* dudeTexture = nullptr;
    SDL_Rect dudeDestRect;
    dudeDestRect.x = 0;
    dudeDestRect.y = 0;
    dudeDestRect.h = 64;
    dudeDestRect.w = 24;
    SDL_FillRect(SDL_GetWindowSurface(win), &dudeDestRect, SDL_MapRGB(SDL_GetWindowSurface(win)->format, 255, 23, 255));
    SDL_Surface* loadedSurface = SDL_LoadBMP("textures/randomdude.bmp");
    SDL_Surface* optimizedSurface = SDL_ConvertSurface(loadedSurface, SDL_GetWindowSurface(win)->format, NULL);
    if (!loadedSurface)
    {
        std::cout << "Surface not loaded";
    }

    dudeTexture = SDL_CreateTextureFromSurface(ren, optimizedSurface);

    SDL_FreeSurface(optimizedSurface);

    bool quit = false;
    while (!quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_RETURN:
                    quit = true;
                case SDLK_a:
                    dudeDestRect.x -= 5;
                    break;
                case SDLK_d:
                    dudeDestRect.x += 5;
                    break;
                default:
                    break;
                }
            }
        }
        SDL_Rect outlineRect = { 25, 25, 12, 32 };
        SDL_SetRenderDrawColor(ren, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(ren, &outlineRect);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, dudeTexture, nullptr, &dudeDestRect);

        SDL_RenderPresent(ren);
    }

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    SDL_Quit();
    return 0;
}