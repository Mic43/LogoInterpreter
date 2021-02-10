#include "TurtleState.h"


void TurtleState::go(double steps,int dir)
{
	 Position newPosition;
	 int i = 0;
	 do
	 {
	 	newPosition = getNewTurtlePosition(&turtle, dir);
	 	if (!validPosition(newPosition))
	 		break;
	
	 	boardState[turtle.y][turtle.x] = true;
	
	 	turtle = newPosition;
	
	 	i++;
	 }
	 while (i < steps);
}

void TurtleState::backward(double steps)
{
	go(steps, -1);
}

void TurtleState::forward(double steps)
{
	go(steps, 1);
}
void TurtleState::turn(int degrees)
{
	angle -= degrees;
}
