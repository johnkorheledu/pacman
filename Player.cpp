#include "Player.h"
#include <string>

Player::Player(const std::string name, const bool is_human)
{
    name_ = name;
    is_human_ = is_human;
    points_ = 0;
    has_Treasure_ = false;
    isDead_ = false;
}

void Player::ChangePoints(const int x)
{
    points_ += x;
}

void Player::SetPosition(Position pos)
{
    pos_ = pos;
}

void Player::SetHasTreasure(bool hastreasure)
{
    has_Treasure_ = hastreasure;
}

void Player::SetIsDead(bool isdead)
{
    isDead_ = isdead;
}

std::string Player::ToRelativePosition(Position other)
{
    if (pos_.row > other.row)
    {
        return "up";
    }
    else if (pos_.row < other.row)
    {
        return "down";
    }
    else if (pos_.col > other.col)
    {
        return "left";
    }
    else if (pos_.col < other.col)
    {
        return "right";
    }
    else
    {
        return "";
    }
}

std::string Player::Stringify()
{
    std::string s = name_ + ": " + std::to_string(points_);
    return s;
}
