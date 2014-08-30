#include "Game.h"
int Game::Run()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    //init window, get win surface
    SDL_Window* win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_SetWindowFullscreen(win, SDL_WINDOW_INPUT_FOCUS);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(ren, 6, 0xFF, 0xFF, 0xFF);
    std::unique_ptr<Entity> dude(new Entity);
    SDL_Surface* loadedSurface = SDL_LoadBMP("textures/randomdude.bmp");
    SDL_Surface* optimizedSurface = SDL_ConvertSurface(loadedSurface, SDL_GetWindowSurface(win)->format, NULL);
    SDL_SetColorKey(optimizedSurface, SDL_TRUE, SDL_MapRGB(optimizedSurface->format, 255, 0, 255));
    if (!loadedSurface)
    {
        std::cout << "Surface not loaded";
    }

    dude->SetTexture(ren, optimizedSurface);
    dude->SetPosition(250, 250);
    SDL_FreeSurface(optimizedSurface);
    SDL_FreeSurface(loadedSurface);

    SDL_Rect rectToDraw = { 100, 100, 100, 100 };

    bool quit = false;
    bool keysHeld[323] = { false };
    bool isJumping = false, isFalling = false;
    int targetHeight = 0;

    Uint32 lastFrame = 0, currentFrame = 0, delay = 0;
    while (!quit)
    {
        currentFrame = SDL_GetTicks();
        if (currentFrame > lastFrame)
            delay = currentFrame - lastFrame;
        lastFrame = currentFrame;
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_KEYDOWN)
            {
                keysHeld[e.key.keysym.sym] = true;
            }
            if (e.type == SDL_KEYUP)
            {
                keysHeld[e.key.keysym.sym] = false;
            }
        }

        if (keysHeld[SDLK_a])
            dude->Move(-0.7 * delay, 0);
        if (keysHeld[SDLK_d])
            dude->Move(0.7 * delay, 0);
        if (keysHeld[SDLK_SPACE])
        {
            if (!isJumping)
            {
                isJumping = true;
                isFalling = false;
                targetHeight = dude->GetDestRect().y - 200;
            }
        }

        if (isJumping && targetHeight < dude->GetDestRect().y)
        {
            dude->Move(0, -0.5 * delay);
        }
        else
        {
            isJumping = false;
            isFalling = true;
        }
        if (isFalling)
        {
            dude->Move(0, 0.3 * delay);
        }

        if (keysHeld[SDLK_RETURN])
            quit = true;

        SDL_RenderClear(ren);
        dude->Draw(ren);
        SDL_RenderPresent(ren);
    }
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);

    SDL_Quit();
}