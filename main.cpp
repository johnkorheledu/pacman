#include <iostream>
#include "Player.h"
#include "Game.h"


int main() {
    // Stationary traps was the extra credit component.
    Player human("human", true);
    Player enemy1("enemy1", false);
    Player enemy2("enemy2", false);

    std::vector<Player*> enemies;
    enemies.push_back(&enemy1);
    enemies.push_back(&enemy2);

    Game game;
    game.NewGame(&human, enemies, 2);

    return 0;
}