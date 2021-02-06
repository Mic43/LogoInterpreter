#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

class Command;
class TurtleState;
class Procedure
{
	std::vector<std::string> parameters;
	std::string name;
	Command* body;


public:
	Command* get_body() const
	{
		return body;
	}

	const std::vector<std::string>& get_parameters() const
	{
		return parameters;
	}

	std::string get_name() const
	{
		return name;
	}
};


class CommandsEnvironment
{
	std::map<std::string, double> variables;
	std::map<std::string, Procedure*> functions;	
	TurtleState* turtle_state;

public:
	TurtleState* get_turtle_state() const
	{
		return turtle_state;
	}

	const std::map<std::string, double>& get_variables() const
	{
		return variables;
	}

	const std::map<std::string, Procedure*>& get_functions() const
	{
		return functions;
	}

	Procedure* getProcedure(const std::string& name) const;
	bool tryAddNewProcedure(Procedure* newFunction);
	double getVariableValue(const std::string& name) const;

	static CommandsEnvironment createNestedEnvironment(
		const CommandsEnvironment& base, 
		const std::map<std::string, double>& newVariables);
	
	
	
};

