#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Game.h"

int main(int argc, char *args[])
{
   
    Game game;
    return game.Run();

    _CrtDumpMemoryLeaks();
}