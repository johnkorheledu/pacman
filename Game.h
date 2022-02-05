#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include "Player.h"

enum class SquareType
{
	Wall,
	Dots,
	Pacman,
	Treasure,
	Enemies,
	Empty,
	PowerfulPacman,
	Trap,
	EnemySpecialTreasure
};
std::string SquareTypeStringify(SquareType sq);
SquareType GetSquareType(char c);

class Board
{
public:
	Board();

	int get_rows() const { return 10; }
	int get_cols() const { return 10; }
	SquareType get_square_value(Position pos) const;

	SquareType GetTreasureOrPellet();
	void SetSquareValue(Position pos, SquareType value);
	std::vector<Position> GetMoves(Player *p);
	bool MovePlayer(Player *p, Position pos, std::vector<Player *> enemylist);
	bool MoveEnemy(Player *p, Position pos);
	void PrettyPrint(Player *p);

private:
	SquareType arr_[10][10];
	int rows_;
	int cols_;
};

class Game
{
public:
	Game();
	int get_dots_count() const { dots_count_;}
	void NewGame(Player *human, std::vector<Player *> enemylist, const int enemies);
	void TakeTurn(Player *p, std::vector<Player *> enemylist);
	void TakeTurnEnemy(Player *p);
	bool IsGameOver(Player *p);
	bool CheckIfDotsOver();
	std::string GenerateReport(Player *p);
	void PrettyPrint();

private:
	Board *board_;
	std::vector<Player *> players_;
	int turn_count_;
	int dots_count_;
	bool game_over_;
};

#endif // _GAME_H_
