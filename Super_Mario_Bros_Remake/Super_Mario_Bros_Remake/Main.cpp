#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    Game game;
    while (game.getWindow()->isOpen())
    {
        game.update();
        game.render();
    }
}