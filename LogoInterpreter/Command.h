#pragma once

#include <string>
#include <utility>
#include <vector>


#include "CommandsEnvironment.h"
#include "Expression.h"

class CommandsVisitorBase;

class Command
{
public:
	virtual void accept(CommandsVisitorBase&) = 0;
};
class SingleCommand : public Command
{

};

class EmptyCommand : public SingleCommand
{
	// Inherited via SingleCommand
	virtual void accept(CommandsVisitorBase&) override;
	
};

class SequentialCommand : public Command
{
public:

	
	SequentialCommand(SingleCommand* c, Command* n) : command(c),nextCommand(n)
	{

	}

public:
	SingleCommand* get_command() const
	{
		return command;
	}

	Command* get_next_command() const
	{
		return nextCommand;
	}

private:
	SingleCommand* command;
	Command* nextCommand;
	
	// Inherited via Command
	virtual void accept(CommandsVisitorBase&) override;

};

class CallCommand : public SingleCommand
{
public:
	std::vector<Expression*> get_parameters() const
	{
		return parameters;
	}

	std::string get_target_name() const
	{
		return targetName;
	}

	void accept(CommandsVisitorBase&) override;

	CallCommand(const std::vector<Expression*>& parameters, const std::string& target_name)
		: parameters(parameters),
		  targetName(target_name)
	{
	}

private:
	std::vector<Expression*> parameters;
	std::string targetName;
};



class DeclareFunctionCommand : public SingleCommand
{
public:
	UserDefinedFunction* get_target() const
	{
		return target;
	}

private:
	UserDefinedFunction* target;
public:
	explicit DeclareFunctionCommand(UserDefinedFunction* target)
		: target(target)
	{
	}

	void accept(CommandsVisitorBase&) override;


};