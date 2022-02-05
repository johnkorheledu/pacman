/**
John Korhel
Homework 1
This program creates an exciting UI for a user to play Pacman.
Stationary traps were the extra credit component I added.
*/

#include <iostream>
#include "Player.h"
#include "Game.h"

int main()
{
    Player human("human", true);
    Player enemy1("enemy1", false);
    Player enemy2("enemy2", false);
    std::vector<Player *> enemies;
    enemies.push_back(&enemy1);
    enemies.push_back(&enemy2);
    Game game;
    game.NewGame(&human, enemies, 2);
    return 0;
}