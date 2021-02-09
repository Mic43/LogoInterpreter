#pragma once

#include <string>
#include <utility>
#include <vector>

#include "Expression.h"
//#include "Visitor.h"

class Procedure;
class CommandsVisitorBase;

class Command
{
public:
	virtual void accept(CommandsVisitorBase&) const = 0;
};
class SingleCommand : public Command
{

};

class EmptyCommand : public SingleCommand
{
	// Inherited via SingleCommand
	virtual void accept(CommandsVisitorBase&) const override;
	
};

class SequentialCommand : public Command
{
public:
	SequentialCommand(std::shared_ptr<SingleCommand> command, std::shared_ptr<Command> next_command)
		: command(command),
		  nextCommand(next_command)
	{
	}

	const SingleCommand& get_command() const
	{
		return *command;
	}

	const Command& get_next_command() const
	{
		return *nextCommand;
	}

private:
	std::shared_ptr<SingleCommand> command;
	std::shared_ptr<Command> nextCommand;
	
	// Inherited via Command
	virtual void accept(CommandsVisitorBase&) const  override;

};

class CallCommand : public SingleCommand
{
public:
	 const std::vector<std::shared_ptr<Expression>>& get_parameters() const
	 {
	 	return parameters;
	 }

	std::string get_target_name() const
	{
		return targetName;
	}

	void accept(CommandsVisitorBase&) const override;

	CallCommand(std::vector<std::shared_ptr<Expression>> parameters, const std::string& target_name)
		: parameters(std::move(parameters)),
		  targetName(target_name)
	{
	}

private:
	std::vector<std::shared_ptr<Expression>> parameters;
	std::string targetName;
};

class DeclareProcedureCommand : public SingleCommand
{
public:
	std::shared_ptr<Procedure> get_target() const
	{
		return target;
	}

private:	
	std::shared_ptr<Procedure> target;
public:
	explicit DeclareProcedureCommand(std::shared_ptr<Procedure> target):
		target(std::move(target)) {
		
	}


	void accept(CommandsVisitorBase&)  const override;


};

 class TurtleCommand: public SingleCommand
 {
 private :
	 std::shared_ptr<Expression> parameter;
 public:
 	enum class Direction {Left,Top,Right,Bottom};

    TurtleCommand(std::shared_ptr<Expression> parameter, Direction direction)
	    : parameter(std::move(parameter)),
	      direction(direction)
    {
    }

    Expression& get_parameter() const
    {
	    return *parameter;
    }

    Direction get_direction() const
    {
	    return direction;
    }

 	void accept(CommandsVisitorBase& v)  const override;
	static std::shared_ptr<TurtleCommand> tryCreate(
		const std::string& identifier, 
		const std::vector<std::shared_ptr<Expression>> &parameter)
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
	

private:
	std::shared_ptr<Expression> condition_;
	std::shared_ptr<Command> body_;
public:


	const Expression& get_condition() const
	{
		return *condition_;
	}

	const Command& get_body() const
	{
		return *body_;
	}

	IfCommand(std::shared_ptr<Expression> condition, std::shared_ptr<Command> body)
		: condition_(std::move(condition)),
		  body_(std::move(body))
	{
	}

	void accept(CommandsVisitorBase&)  const override;
};