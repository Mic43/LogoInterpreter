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

	

	 Position getNewTurtlePosition(Position* t,int size)
	 {
		double rad = angle * 3.14156 / 180.0;
	 	
		double x = -size * sin((-rad));
		double y = size * cos(-rad);
	 	
		Position change(round(x), round(y));
	 	
		// if (!validPosition(newPosition))
		// 	return;
		// turtle = newPosition;
	
	 	Position res;
	 	res.x = t->x + change.x;
	 	res.y = t->y + change.y;
	
	 	return  res;
	 }

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
		: angle(180), boardSize(board_size),
		  boardState(board_size, std::vector<bool>(board_size, false)),
		  turtle(board_size / 2, board_size / 2)
	{
	}

	void forward(double steps);
	void go(double steps, int dir);
	void backward(double steps);
	void turn(int degrees);

};

