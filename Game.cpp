#include "Game.h"
#include <string>
#include <iostream>

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
        return " | ";
    case SquareType::Dots:
        return " . ";
    case SquareType::Pacman:
        return " p ";
    case SquareType::Treasure:
        return " T ";
    case SquareType::Enemies:
        return " e ";
    case SquareType::Empty:
        return " _ ";
    case SquareType::PowerfulPacman:
        return " P2 ";
    case SquareType::Trap:
        return "Trap";
    case SquareType::EnemySpecialTreasure:
        return "EnemySpecialTreasure";
    default:
        return "";
    }
}

SquareType GetSquareType(char c)
{
    switch (c)
    {
    case '|':
        return SquareType::Wall;
    case '.':
        return SquareType::Dots;
    case 'p':
        return SquareType::Pacman;
    case 'T':
        return SquareType::Treasure;
    case 'e':
        return SquareType::Enemies;
    case '_':
        return SquareType::Empty;
    case 'P':
        return SquareType::PowerfulPacman;
    case 't':
        return SquareType::Trap;
    case 'E':
        return SquareType::EnemySpecialTreasure;
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
    SetSquareValue({0, 4}, SquareType::Wall);
    SetSquareValue({0, 5}, SquareType::Wall);
    SetSquareValue({0, 6}, SquareType::Wall);
    SetSquareValue({0, 7}, SquareType::Wall);
    SetSquareValue({0, 8}, SquareType::Wall);
    SetSquareValue({1, 2}, SquareType::Wall);
    SetSquareValue({1, 3}, SquareType::Wall);
    SetSquareValue({1, 5}, SquareType::Wall);
    SetSquareValue({1, 8}, SquareType::Wall);
    SetSquareValue({2, 2}, SquareType::Wall);
    SetSquareValue({2, 3}, SquareType::Wall);
    SetSquareValue({2, 5}, SquareType::Wall);
    SetSquareValue({3, 3}, SquareType::Treasure);
    SetSquareValue({3, 5}, SquareType::Wall);
    SetSquareValue({3, 6}, SquareType::Wall);
    SetSquareValue({3, 8}, SquareType::Wall);
    SetSquareValue({4, 1}, SquareType::Wall);
    SetSquareValue({4, 2}, SquareType::Wall);
    SetSquareValue({5, 1}, SquareType::Wall);
    SetSquareValue({5, 2}, SquareType::Wall);
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
    std::vector<Position> moves;
    Position pos = p->get_position();
    //left
    if (pos.row > 0 && get_square_value({pos.row - 1, pos.col}) != SquareType::Wall)
    {
        moves.push_back({pos.row - 1, pos.col});
    }
    //right
    if (pos.row < get_rows() - 1 && get_square_value({pos.row + 1, pos.col}) != SquareType::Wall)
    {
        moves.push_back({pos.row + 1, pos.col});
    }
    //up
    if (pos.col > 0 && get_square_value({pos.row, pos.col - 1}) != SquareType::Wall)
    {
        moves.push_back({pos.row, pos.col - 1});
    }
    //down
    if (pos.col < get_cols() - 1 && get_square_value({pos.row, pos.col + 1}) != SquareType::Wall)
    {
        moves.push_back({pos.row, pos.col + 1});
    }
    return moves;
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
    else if(get_square_value(pos) == SquareType::Empty){
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
            SetSquareValue(p->get_position(), SquareType::Empty);
            SetSquareValue(pos, SquareType::Pacman);
            p->set_position(pos);
            p->change_points(100);
            p->set_treasure_count(p->get_treasure_count() - 1);
            if (p->get_treasure_count() == 0)
            {
                p->set_has_treasure(false);
            }
            else{
                SetSquareValue(pos, SquareType::PowerfulPacman);
            }
            return true;
        }
        //TODO: end the game here
        else
        {
            SetSquareValue(p->get_position(), SquareType::Empty);
            SetSquareValue(pos, SquareType::Pacman);
            p->set_position(pos);
            p->change_points(-1);
            return true;
            exit(0);
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
    Moves an enemy to the given position
    @param p Enemy Player pointer
    @param pos Position to move to
    @return bool True if move was successful, false if move was not successful
*/
bool Board::MoveEnemy(Player *p, Position pos){
    
    
    // move the enemy
    if (get_square_value(pos) == SquareType::Dots)
    {
        SetSquareValue(pos, get_square_value(p->get_position()));
        SetSquareValue(p->get_position(), GetSquareType(p->get_prev_move_type()));
        p->set_prev_move_type('.');
        p->set_position(pos);
        p->change_points(1);
        return true;
    }
    else if (get_square_value(pos) == SquareType::Empty){
        SetSquareValue(pos, get_square_value(p->get_position()));
        SetSquareValue(p->get_position(), GetSquareType(p->get_prev_move_type()));
        p->set_prev_move_type('_');
        p->set_position(pos);
        p->change_points(1);
        return true;
    }
    else if (get_square_value(pos) == SquareType::Treasure){
        SetSquareValue(pos, get_square_value(p->get_position()));
        SetSquareValue(p->get_position(), GetSquareType(p->get_prev_move_type()));
        p->set_prev_move_type('T');
        p->set_position(pos);
        p->change_points(1);
        return true;
    }
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
    std::cout << "Points: " << p->get_points() << '\n';
    std::cout << "Treasure(s): " << p->get_treasure_count() << '\n';
}

/**
    Prints game specific information to the console in a readable format
    @return void
*/
void Game::PrettyPrint()
{
    board_->PrettyPrint(players_[0]);
    std::cout << "Turns: " << turn_count_ << '\n' << '\n';
}

Game::Game() {}

void Game::NewGame(Player *human, std::vector<Player *> enemylist, const int enemies)
{
    turn_count_ = 0;
    board_ = new Board();
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
        TakeTurnEnemy(players_[1]);
        TakeTurnEnemy(players_[2]);
        PrettyPrint();
    }
}
void Game::TakeTurn(Player *p, std::vector<Player *> enemylist)
{
    turn_count_ += 1;
    std::vector<Position> moves = board_->GetMoves(p);
    std::cout << "Valid moves: ";
    for (long unsigned int i = 0; i < moves.size(); i++)
    {
        std::cout << players_[0]->ToRelativePosition(moves[i]) << " ";
    }
    std::cout << '\n';

    // get user input for move and check if valid (up, right, down, left).
    std::string input;
    std::cout << "Enter move: ";
    std::cin >> input;
    Position move;
    if (input == "up")
    {
        move = {p->get_position().row - 1, p->get_position().col};
    }
    else if (input == "right")
    {
        move = {p->get_position().row, p->get_position().col + 1};
    }
    else if (input == "down")
    {
        move = {p->get_position().row + 1, p->get_position().col};
    }
    else if (input == "left")
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
        turn_count_-=1;
        return;
    }
}

void Game::TakeTurnEnemy(Player *p)
{
    std::vector<Position> moves = board_->GetMoves(p);
    int random = rand() % moves.size();
    Position move = moves[random];
    board_->MoveEnemy(p, move);
}

bool Game::IsGameOver(Player *p)
{
    return false;
}
// bool Game::CheckifdotsOver(){}
// std::string Game::GenerateReport(Player *p){}
