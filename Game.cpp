#include "Game.h"
#include <string>
#include <iostream>
#include <algorithm>
/**
    Returns the symbol associated with a given SquareType sq

    @param sq SquareType to be converted to a string
    @return String representation of the SquareType
*/
std::string SquareTypeStringify(SquareType sq)
{
    switch (sq)
    {
    case SquareType::Wall:
        return "|";
    case SquareType::Dots:
        return ".";
    case SquareType::Pacman:
        return "<";
    case SquareType::Treasure:
        return "t";
    case SquareType::Enemies:
        return "e";
    case SquareType::Empty:
        return "_";
    case SquareType::PowerfulPacman:
        return "p";
    case SquareType::Trap:
        return "*";
    case SquareType::EnemySpecialTreasure:
        return "EnemySpecialTreasure";
    default:
        return "";
    }
}

/**
    Returns the SquareType associated with a given char c

    @param c char to be converted to a SquareType
    @return SquareType representation of the char
*/
SquareType GetSquareType(char c)
{
    switch (c)
    {
    case '|':
        return SquareType::Wall;
    case '.':
        return SquareType::Dots;
    case '<':
        return SquareType::Pacman;
    case 't':
        return SquareType::Treasure;
    case 'e':
        return SquareType::Enemies;
    case '_':
        return SquareType::Empty;
    case 'p':
        return SquareType::PowerfulPacman;
    case '*':
        return SquareType::Trap;
    default:
        return SquareType::Empty;
    }
}

/**
    Default constructor for the Board class. Constructs a new Board with the constraints in writeup

    @return Board object
*/
Board::Board()
{
    // Set initial position for two enemies
    SetSquareValue({7, 4}, SquareType::Enemies);
    SetSquareValue({4, 5}, SquareType::Enemies);

    // Populate board with pellets and treasure. 10% chance of treasure and 90% chance of pellets
    for (int i = 0; i < get_rows(); i++)
    {
        for (int j = 0; j < get_cols(); j++)
        {
            if (get_square_value({i, j}) != SquareType::Enemies)
            {
                SetSquareValue({i, j}, GetTreasureOrPellet());
            }
        }
    }

    // Set initial position for Pacman
    SetSquareValue({0, 0}, SquareType::Pacman);
    // Setup basic layout of board. Walls, and two static treasures
    SetSquareValue({0, 4}, SquareType::Trap);
    SetSquareValue({0, 5}, SquareType::Trap);
    SetSquareValue({0, 6}, SquareType::Wall);
    SetSquareValue({0, 7}, SquareType::Trap);
    SetSquareValue({0, 8}, SquareType::Wall);
    SetSquareValue({1, 2}, SquareType::Trap);
    SetSquareValue({1, 3}, SquareType::Wall);
    SetSquareValue({1, 5}, SquareType::Wall);
    SetSquareValue({1, 8}, SquareType::Wall);
    SetSquareValue({2, 2}, SquareType::Wall);
    SetSquareValue({2, 3}, SquareType::Wall);
    SetSquareValue({2, 5}, SquareType::Wall);
    SetSquareValue({3, 3}, SquareType::Treasure);
    SetSquareValue({3, 5}, SquareType::Wall);
    SetSquareValue({3, 6}, SquareType::Wall);
    SetSquareValue({3, 8}, SquareType::Trap);
    SetSquareValue({4, 1}, SquareType::Wall);
    SetSquareValue({4, 2}, SquareType::Wall);
    SetSquareValue({5, 1}, SquareType::Wall);
    SetSquareValue({5, 2}, SquareType::Trap);
    SetSquareValue({5, 3}, SquareType::Wall);
    SetSquareValue({5, 4}, SquareType::Wall);
    SetSquareValue({7, 5}, SquareType::Wall);
    SetSquareValue({7, 6}, SquareType::Wall);
    SetSquareValue({7, 8}, SquareType::Treasure);
    SetSquareValue({8, 5}, SquareType::Wall);
    SetSquareValue({8, 6}, SquareType::Wall);
    SetSquareValue({8, 7}, SquareType::Wall);
    SetSquareValue({8, 8}, SquareType::Wall);
    SetSquareValue({8, 9}, SquareType::Wall);
    SetSquareValue({9, 5}, SquareType::Wall);
    SetSquareValue({9, 6}, SquareType::Wall);
    SetSquareValue({9, 7}, SquareType::Wall);
    SetSquareValue({9, 8}, SquareType::Wall);
    SetSquareValue({9, 9}, SquareType::Wall);
}

/**
    Returns the SquareType of the square at the given position on the board

    @param pos Position of the square to be returned
    @return SquareType of the square at the given position
*/
SquareType Board::get_square_value(Position pos) const
{
    return arr_[pos.row][pos.col];
}

/**
    Returns SquareType of either a pellet or treasure, where treasure is a 1 in 10 chance
    @return SquareType of either a pellet or treasure
*/
SquareType Board::GetTreasureOrPellet()
{
    int random = rand() % 100;
    if (random < 10)
    {
        return SquareType::Treasure;
    }
    else
    {
        return SquareType::Dots;
    }
}

/**
    Sets the SquareType of the square at the given position on the board

    @param pos Position of the square to be set
    @param sq SquareType to be set
    @return void
*/
void Board::SetSquareValue(Position pos, SquareType sq)
{
    arr_[pos.row][pos.col] = sq;
}

/**
    Returns a vector of type Position containing all legal moves for the player at their position

    @param p Player pointer
    @return Position Vector of legal moves
*/
std::vector<Position> Board::GetMoves(Player *p)
{
    if (p->is_human())
    {
        // print current position of player
        std::cout << "Current Position: " << p->get_position().row << " " << p->get_position().col << std::endl;
        std::vector<Position> moves;
        Position pos = p->get_position();
        // down
        if (pos.row > 0 && get_square_value({pos.row - 1, pos.col}) != SquareType::Wall)
        {
            moves.push_back({pos.row - 1, pos.col});
        }
        if (pos.row < get_rows() - 1 && get_square_value({pos.row + 1, pos.col}) != SquareType::Wall)
        {
            moves.push_back({pos.row + 1, pos.col});
        }
        if (pos.col > 0 && get_square_value({pos.row, pos.col - 1}) != SquareType::Wall)
        {
            moves.push_back({pos.row, pos.col - 1});
        }
        if (pos.col < get_cols() - 1 && get_square_value({pos.row, pos.col + 1}) != SquareType::Wall)
        {
            moves.push_back({pos.row, pos.col + 1});
        }
        return moves;
    }
    else
    {
        std::vector<Position> moves;
        Position pos = p->get_position();
        // up
        if (pos.row > 0 && get_square_value({pos.row - 1, pos.col}) != SquareType::Wall)
        {
            moves.push_back({pos.row - 1, pos.col});
        }
        // down
        if (pos.row < get_rows() - 1 && get_square_value({pos.row + 1, pos.col}) != SquareType::Wall)
        {
            moves.push_back({pos.row + 1, pos.col});
        }
        // left
        if (pos.col > 0 && get_square_value({pos.row, pos.col - 1}) != SquareType::Wall)
        {
            moves.push_back({pos.row, pos.col - 1});
        }
        // right
        if (pos.col < get_cols() - 1 && get_square_value({pos.row, pos.col + 1}) != SquareType::Wall)
        {
            moves.push_back({pos.row, pos.col + 1});
        }
        // up-left
        if (pos.row > 0 && pos.col > 0 && get_square_value({pos.row - 1, pos.col - 1}) != SquareType::Wall)
        {
            moves.push_back({pos.row - 1, pos.col - 1});
        }
        // up-right
        if (pos.row > 0 && pos.col < get_cols() - 1 && get_square_value({pos.row - 1, pos.col + 1}) != SquareType::Wall)
        {
            moves.push_back({pos.row - 1, pos.col + 1});
        }
        // down-left
        if (pos.row < get_rows() - 1 && pos.col > 0 && get_square_value({pos.row + 1, pos.col - 1}) != SquareType::Wall)
        {
            moves.push_back({pos.row + 1, pos.col - 1});
        }
        // down-right
        if (pos.row < get_rows() - 1 && pos.col < get_cols() - 1 && get_square_value({pos.row + 1, pos.col + 1}) != SquareType::Wall)
        {
            moves.push_back({pos.row + 1, pos.col + 1});
        }
        return moves;
    }
}

/**
    Moves the player to the given position

    @param p Player pointer
    @param pos Position to move to
    @param enemylist Vector of enemy player pointers
    @return bool True if move was successful, false if move was not successful
*/
bool Board::MovePlayer(Player *p, Position pos, std::vector<Player *> enemylist)
{
    if (get_square_value(pos) == SquareType::Dots)
    {
        SetSquareValue(pos, get_square_value(p->get_position()));
        SetSquareValue(p->get_position(), SquareType::Empty);
        p->set_position(pos);
        p->change_points(1);
        return true;
    }
    else if (get_square_value(pos) == SquareType::Trap)
    {
        SetSquareValue(pos, get_square_value(p->get_position()));
        SetSquareValue(p->get_position(), SquareType::Empty);
        p->set_position(pos);
        p->change_points(-10);
        p->set_lives(p->get_lives() - 1);
        return true;
    }
    else if (get_square_value(pos) == SquareType::Empty)
    {
        SetSquareValue(pos, get_square_value(p->get_position()));
        SetSquareValue(p->get_position(), SquareType::Empty);
        p->set_position(pos);
        return true;
    }
    else if (get_square_value(pos) == SquareType::Treasure)
    {
        SetSquareValue(p->get_position(), SquareType::Empty);
        SetSquareValue(pos, SquareType::PowerfulPacman);
        p->set_position(pos);
        p->change_points(100);
        p->set_treasure_count(p->get_treasure_count() + 1);
        p->set_has_treasure(true);
        return true;
    }
    else if (get_square_value(pos) == SquareType::Enemies)
    {
        if (p->has_treasure())
        {
            for (long unsigned int i = 0; i < enemylist.size(); i++)
            {
                if (enemylist[i]->get_position() == pos)
                {
                    enemylist[i]->set_is_dead(true);
                }
            }
            SetSquareValue(p->get_position(), SquareType::Empty);
            SetSquareValue(pos, SquareType::Pacman);
            p->set_position(pos);
            p->change_points(100);
            p->set_treasure_count(p->get_treasure_count() - 1);
            if (p->get_treasure_count() == 0)
            {
                p->set_has_treasure(false);
            }
            else
            {
                SetSquareValue(pos, SquareType::PowerfulPacman);
            }
            return true;
        }
        else
        {
            SetSquareValue(p->get_position(), SquareType::Empty);
            SetSquareValue(pos, SquareType::Pacman);
            p->set_position(pos);
            p->set_is_dead(true);
            return true;
        }
    }
    else if (get_square_value(pos) == SquareType::Wall)
    {
        return false;
    }
    else
    {
        return false;
    }
}

/**
    Generates a report after the game is over

    @param p Player pointer
    @return std::string Report of the game
*/
std::string Game::GenerateReport(Player *p)
{
    std::string report = "";
    report += "Pacman Score: " + std::to_string(p->get_points()) + "\n";
    report += "\n";
    return report;
}

/**
    Moves an enemy to the given position

    @param p Enemy Player pointer
    @param pos Position to move to
    @return bool True if move was successful, false if move was not successful
*/
bool Board::MoveEnemy(Player *p, Position pos)
{
    if (get_square_value(pos) == SquareType::Pacman)
    {
        p->set_enemy_prev_type(SquareTypeStringify((get_square_value(pos)))[0]);
        SetSquareValue(pos, get_square_value(p->get_position()));
        SetSquareValue(p->get_position(), GetSquareType(p->get_enemy_prev_type()));
        p->set_position(pos);
    }
    else
    {
        p->set_enemy_prev_type(SquareTypeStringify((get_square_value(pos)))[0]);
        SetSquareValue(pos, get_square_value(p->get_position()));
        SetSquareValue(p->get_position(), GetSquareType(p->get_enemy_prev_type()));
        p->set_position(pos);
        return true;
    }
    return false;
}

/**
    Prints the board to the console in a readable format

    @param p Player pointer
    @return void
*/
void Board::PrettyPrint(Player *p)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            std::cout << SquareTypeStringify(get_square_value({i, j}));
        }
        std::cout << std::endl;
    }
    std::cout << p->Stringify() << std::endl;
}

/**
    Prints game specific information to the console in a readable format

    @return void
*/
void Game::PrettyPrint()
{
    board_->PrettyPrint(players_[0]);
    std::cout << "Turns: " << turn_count_ << '\n';
    std::cout << "Dots remaining: " << get_dots_count(board_) << '\n';
    std::cout << "Treasure remaining: " << get_treasures_count(board_) << '\n';
}

/**
    Prints game specific information to the console in a readable format

    @return void
*/
Game::Game()
{
    turn_count_ = 0;
    board_ = new Board();
    dots_count_ = get_dots_count(board_);
}

/**
    Checks if there are dots remaining on the board

    @return True if there are no more dots on the board, false if there are still dots on the board
*/
bool Game::CheckIfDotsOver()
{
    if (get_dots_count(board_) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
    Checks if there are treasures remaining on the board

    @return True if there are still treasures on the board, false if there are no more treasures on the board
*/
bool Game::CheckIfTreasuresOver()
{
    if (get_treasures_count(board_) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
    Get the number of dots remaining on the board

    @param board Board pointer
    @return Number of dots remaining on the board
*/
int Game::get_dots_count(Board *board)
{
    int count = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (board->get_square_value({i, j}) == SquareType::Dots)
            {
                count++;
            }
        }
    }
    return count;
}

/**
    Get the number of treasures remaining on the board

    @param board Board pointer
    @return Number of treasures remaining on the board
*/
int Game::get_treasures_count(Board *board)
{
    int count = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (board->get_square_value({i, j}) == SquareType::Treasure)
            {
                count++;
            }
        }
    }
    return count;
}

/**
    Create a new game

    @param human Player pointer
    @param enemylist List of enemy players
    @param enemies Number of enemies
    @return void
*/
void Game::NewGame(Player *human, std::vector<Player *> enemylist, const int enemies)
{
    players_.push_back(human);
    for (long int i = 0; i < enemies; i++)
    {
        players_.push_back(enemylist[i]);
    }
    players_[0]->set_position({0, 0});
    players_[1]->set_position({7, 4});
    players_[2]->set_position({4, 5});

    PrettyPrint();

    while (!IsGameOver(players_[0]))
    {
        TakeTurn(players_[0], enemylist);
        for (long unsigned int i = 0; i < enemylist.size(); i++)
        {
            if (enemylist[i]->is_dead() == false)
            {
                TakeTurnEnemy(enemylist[i]);
            }
        }
        PrettyPrint();
    }
    std::cout << "Game Over!\n";
    std::cout << GenerateReport(players_[0]);
}

/**
    Takes a turn for a player

    @param p Player pointer
    @param enemylist List of enemy players
    @return void
*/
void Game::TakeTurn(Player *p, std::vector<Player *> enemylist)
{
    turn_count_ += 1;
    std::vector<Position> moves = board_->GetMoves(p);
    std::cout << "Valid moves: ";
    std::vector<std::string> relative_moves;
    for (long unsigned int i = 0; i < moves.size(); i++)
    {
        std::cout << players_[0]->ToRelativePosition(moves[i]) << " ";
        relative_moves.push_back(players_[0]->ToRelativePosition(moves[i]));
    }
    std::cout << '\n';
    std::string input;
    std::cout << "Enter move: ";
    std::cin >> input;
    Position move;
    if (input == "up" && std::find(relative_moves.begin(), relative_moves.end(), "UP") != relative_moves.end())
    {
        move = {p->get_position().row - 1, p->get_position().col};
    }
    else if (input == "right" && std::find(relative_moves.begin(), relative_moves.end(), "RIGHT") != relative_moves.end())
    {
        move = {p->get_position().row, p->get_position().col + 1};
    }
    else if (input == "down" && std::find(relative_moves.begin(), relative_moves.end(), "DOWN") != relative_moves.end())
    {
        move = {p->get_position().row + 1, p->get_position().col};
    }
    else if (input == "left" && std::find(relative_moves.begin(), relative_moves.end(), "LEFT") != relative_moves.end())
    {
        move = {p->get_position().row, p->get_position().col - 1};
    }
    else
    {
        turn_count_ -= 1;
        std::cout << "Invalid move.\n";
        return;
    }
    if (board_->MovePlayer(p, move, enemylist))
    {
        return;
    }
    else
    {
        std::cout << "Invalid move.\n";
        turn_count_ -= 1;
        return;
    }
}

/**
    Takes a turn for an enemy player

    @param p Player pointer
    @return void
*/
void Game::TakeTurnEnemy(Player *p)
{
    std::vector<Position> moves = board_->GetMoves(p);
    int rand_move = rand() % moves.size();
    while (board_->get_square_value(moves[rand_move]) == SquareType::PowerfulPacman)
    {
        rand_move = rand() % moves.size();
    }
    board_->MoveEnemy(p, moves[rand_move]);
}

/**
    Checks if the game is over

    @param p Player pointer
    @return True if the game is over, false if the game is not over
*/
bool Game::IsGameOver(Player *p)
{
    return p->is_dead() || (CheckIfDotsOver() && CheckIfTreasuresOver()) || p->get_lives() == 0;
}