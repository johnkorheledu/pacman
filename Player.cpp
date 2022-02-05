#include "Player.h"
#include <string>

Player::Player(const std::string name, const bool is_human)
{
    name_ = name;
    is_human_ = is_human;
    points_ = 0;
    has_treasure_ = false;
    treasure_count_ = 0;
    is_dead_ = false;
    prev_move_type_ = 'Dots';
}

void Player::change_points(const int x)
{
    points_ += x;
}

void Player::set_prev_move_type(char sq)
{
    prev_move_type_ = sq;
}
void Player::set_position(Position pos)
{
    pos_ = pos;
}

void Player::set_has_treasure(bool hastreasure)
{
    has_treasure_ = hastreasure;
}

void Player::set_is_dead(bool isdead)
{
    is_dead_ = isdead;
}


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

void Player::set_treasure_count(int count)
{
    treasure_count_ = count;
}

std::string Player::Stringify()
{
    std::string s = name_ + ": " + std::to_string(points_);
    return s;
}
