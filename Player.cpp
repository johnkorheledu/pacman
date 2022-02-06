#include "Player.h"
#include <string>

/**
    Returns a new Player object

    @param name The name of the player.
    @param is_human Whether the player is human or not
    @return A new Player object
*/
Player::Player(const std::string name, const bool is_human)
{
    name_ = name;
    is_human_ = is_human;
    points_ = 0;
    has_treasure_ = false;
    treasure_count_ = 0;
    is_dead_ = false;
    enemy_prev_type_ = '.';
    treasure_count_ = 0;
    if (is_human_)
    {
        lives_ = 3;
    }
    else
    {
        lives_ = 1;
    }
}

/**
    Sets the player's lives

    @param lives The number of lives to set
    @return void
*/
void Player::set_lives(int lives)
{
    lives_ = lives;
}

/**
    Updates the player's points

    @param x The amount to change the player's points by
    @return void
*/
void Player::change_points(const int x)
{
    points_ += x;
}

/**
    Update the enemy's previous square type

    @param type The type of square the enemy was on
    @return void
*/
void Player::set_enemy_prev_type(char type)
{
    enemy_prev_type_ = type;
}

/**
    Displays useful information about the player

    @return A string representation of points, treasure count, lives, and player name.
*/
std::string Player::Stringify()
{
    // get players points, treasure count, and lives
    std::string str = "";
    str += "Player: " + name_ + "\n";
    str += "Points: " + std::to_string(points_) + "\n";
    str += "Treasure Count: " + std::to_string(treasure_count_) + "\n";
    str += "Lives: " + std::to_string(lives_);
    return str;
}

/**
    Sets the player's position

    @param pos The position to set the player to
    @return void
*/
void Player::set_position(Position pos)
{
    pos_ = pos;
}

/**
    Sets the player's treasure boolean

    @param hastreasure Whether the player has treasure or not
    @return void
*/
void Player::set_has_treasure(bool hastreasure)
{
    has_treasure_ = hastreasure;
}

/**
    Sets the player's dead boolean

    @param isdead Whether the player is dead or not
    @return void
*/
void Player::set_is_dead(bool isdead)
{
    is_dead_ = isdead;
}

/**
    Converts a position to a relative position

    @param other The position to convert to a relative position
    @return A string representation of the relative position
*/
std::string Player::ToRelativePosition(Position other)
{
    if (pos_.row > other.row)
    {
        return "UP";
    }
    else if (pos_.row < other.row)
    {
        return "DOWN";
    }
    else if (pos_.col > other.col)
    {
        return "LEFT";
    }
    else if (pos_.col < other.col)
    {
        return "RIGHT";
    }
    else
    {
        return "";
    }
}

/**
    Sets the player's treasure count

    @param count The amount to change the player's treasure count to
    @return void
*/
void Player::set_treasure_count(int count)
{
    treasure_count_ = count;
}
