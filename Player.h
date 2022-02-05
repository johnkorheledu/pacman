#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
struct Position
{
	int row;
	int col;
	bool operator==(const Position &other)
	{
		return row == other.row && col == other.col;
	}
};

class Player
{
public:
	Player(const std::string name, const bool is_human);

	std::string get_name() const { return name_; }
	int get_points() const { return points_; }
	Position get_position() const { return pos_; }
	bool is_human() const { return is_human_; }
	bool has_treasure() const { return has_treasure_; }
	int get_treasure_count() const { return treasure_count_; }
	bool is_dead() const { return is_dead_; }
	char get_prev_move_type() const {return prev_move_type_; }

	void change_points(const int x);
	void set_position(Position pos);
	void set_has_treasure(bool hastreasure);
	void set_is_dead(bool isdead);
	void set_treasure_count(int count);
	void set_prev_move_type(char sq);

	std::string ToRelativePosition(Position other);
	std::string Stringify();

private:
	std::string name_;
	int points_;
	Position pos_;
	bool is_human_;
	bool has_treasure_;
	bool is_dead_;
	int treasure_count_;
	char prev_move_type_;
};

#endif // _PLAYER_H_
