#include "TurtleState.h"


void TurtleState::forward(double steps)
{
	Position newPosition (-steps * sin((-angle)),steps*cos(-angle));
	if (!validPosition(newPosition))
		return;
	turtle = newPosition;
		// 		break;
	// Position newPosition;
	// int i = 0;
	// do
	// {
	// 	newPosition = getNewTurtlePosition(&turtle);
	// 	if (!validPosition(newPosition))
	// 		break;
	//
	// 	boardState[turtle.y][turtle.x] = true;
	//
	// 	turtle = newPosition;
	//
	// 	i++;
	// }
	// while (i < steps);
}

void TurtleState::backward(int steps)
{
	forward(-steps);
}

void TurtleState::turn(int degrees)
{
	angle += degrees;
}
