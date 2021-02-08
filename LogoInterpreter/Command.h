#pragma once

#include <string>
#include <utility>
#include <vector>


#include "CommandsEnvironment.h"
#include "Expression.h"
//#include "Visitor.h"

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

class DeclareProcedureCommand : public SingleCommand
{
public:
	Procedure* get_target() const
	{
		return target;
	}

private:
	Procedure* target;
public:
	explicit DeclareProcedureCommand(Procedure* target)
		: target(target)
	{
	}

	void accept(CommandsVisitorBase&) override;


};

 class TurtleCommand: public SingleCommand
 {
 private :
 	Expression* parameter;
 public:
 	enum class Direction {Left,Top,Right,Bottom};

    TurtleCommand(Expression* parameter, Direction direction)
	    : parameter(parameter),
	      direction(direction)
    {
    }

    Expression* get_parameter() const
    {
	    return parameter;
    }

    Direction get_direction() const
    {
	    return direction;
    }

 	void accept(CommandsVisitorBase& v) override;
	static std::shared_ptr<TurtleCommand> tryCreate(const std:: string& identifier, const std::vector<Expression*> &parameter)
	{
		if( identifier == "przod")
			return std::make_shared<TurtleCommand>(parameter.front(), Direction::Top);
		return std::unique_ptr<TurtleCommand>{};
	}
 private:
	 Direction direction;
 };

class IfCommand : public SingleCommand
{
public:
	Expression* get_condition() const
	{
		return condition_;
	}

	Command* get_body() const
	{
		return body_;
	}

private:
	Expression* condition_;
	Command* body_;
public:

	IfCommand(Expression* condition,Command* body): condition_(condition), body_(body)
	{
		
	}
	void accept(CommandsVisitorBase&) override;
};