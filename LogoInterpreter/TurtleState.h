#pragma once
#include <iostream>
#include <vector>


class TurtleState
{

	struct Position
	{
		int x;
		int y;


		Position(int x, int y)
			: x(x),
			  y(y)
		{
		}

		Position() = default;
	};

	int angle;		
	int boardSize;
	std::vector<std::vector<bool>> boardState;
	Position turtle;	

	//double temp {};

	

	// Position getNewTurtlePosition(Position* t)
	// {
	// 	Position change;
	// 	if (direction == Direction::Top)
	// 		change = Position{ 0,-1 };
	// 	else if (direction == Direction::Right)
	// 		change = Position{ 1,0 };
	// 	else if (direction == Direction::Bottom)
	// 		change = Position{ 0,1 };
	// 	else
	// 		change = Position{ -1,0 };
	//
	// 	Position res;
	// 	res.x = t->x + change.x;
	// 	res.y = t->y + change.y;
	//
	// 	return  res;
	// }

	bool validPosition(Position position)
	{
		if (position.y >= boardSize || position.x >= boardSize || position.x < 0 || position.y < 0)
			return false;
		
		return true;
	}


public:
	int get_board_size() const
	{
		return boardSize;
	}
	bool getState(int x,int y)
	{
		return boardState[y][x];
	}


	explicit TurtleState(int board_size)
		: angle(0), boardSize(board_size),
		  boardState(board_size, std::vector<bool>(board_size, false)),
		  turtle(board_size / 2, board_size / 2)
	{
	}

	void forward(double steps);
	void backward(int steps);
	void turn(int degrees);

};

