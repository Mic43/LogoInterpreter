#pragma once
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <stdexcept>

#include "TurtleState.h"
class Command;

class Procedure
{
	std::vector<std::string> parameters;
	std::string name;
	std::shared_ptr<Command> body;

public:
	Procedure(const std::vector<std::string>& parameters, const std::string& name, 
		std::shared_ptr<Command> body)
		: parameters(parameters),
		  name(name), body(std::move(body))

	{
	}

	const Command& get_body() const
	{
		return *body;
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
	std::map<std::string, std::shared_ptr<Procedure>> functions;
	std::shared_ptr<TurtleState> turtle_state;

public:
	CommandsEnvironment(std::shared_ptr<TurtleState> turtle_state): turtle_state(turtle_state)
	{
	}
	
	TurtleState* get_turtle_state() const
	{
		return turtle_state.get();
	}

	const std::map<std::string, double>& get_variables() const
	{
		return variables;
	}

	const std::map<std::string, std::shared_ptr<Procedure>>& get_functions() const
	{
		return functions;
	}

	std::optional<std::reference_wrapper<Procedure>> getProcedure(const std::string& name) const;
	bool tryAddNewProcedure(std::shared_ptr<Procedure> newFunction);
	std::optional<double> getVariableValue(const std::string& name) const;
		
	static CommandsEnvironment createNestedEnvironment(
		const CommandsEnvironment& base, 
		const std::map<std::string, double>& newVariables);
	
	
	
};

