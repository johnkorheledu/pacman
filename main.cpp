#include <iostream>
#include "Player.h"
#include "Game.h"


int main() {
    Player human("human", true);
    Player enemy1("enemy1", false);
    Player enemy2("enemy2", false);

    std::vector<Player*> enemies;
    enemies.push_back(&enemy1);
    enemies.push_back(&enemy2);

    // board.prettyPrint(human_ptr);
    // board.MovePlayer(human_ptr, {0,1}, enemies);
    // board.prettyPrint(human_ptr);
    // board.MovePlayer(human_ptr, {1,1}, enemies);
    // board.prettyPrint(human_ptr);
    // board.MovePlayer(human_ptr, {2,1}, enemies);
    // board.prettyPrint(human_ptr);
    // board.MovePlayer(human_ptr, {3,1}, enemies);
    // board.prettyPrint(human_ptr);

    // board.MovePlayer(human_ptr, {3,2}, enemies);
    // board.prettyPrint(human_ptr);
    // board.MovePlayer(human_ptr, {3,3}, enemies);
    // board.prettyPrint(human_ptr);
    // board.MovePlayer(human_ptr, {3,4}, enemies);
    // board.prettyPrint(human_ptr);

    // board.MovePlayer(human_ptr, {4,4}, enemies);
    // board.prettyPrint(human_ptr);

    // board.MovePlayer(human_ptr, {4,5}, enemies);
    // board.prettyPrint(human_ptr);

    Game game;
    game.NewGame(&human, enemies, 2);

    return 0;
}