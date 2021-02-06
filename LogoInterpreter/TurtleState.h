#pragma once
#include <iostream>

class TurtleState
{
	double state;

public:


	double get_state() const
	{
		return state;
	}

	explicit TurtleState()
		: state(0)
	{
	}

	void test()
	{
		state++;
	}

	void test(double val)
	{
		state += val;
		std::cout << state << std::endl;
	}
};

