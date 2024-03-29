#pragma once

#include <string>
#include <utility>
#include <vector>


#include "CommandsEnvironment.h"
#include "Expression.h"
#include "TurtleState.h"
#include <string>

//#include "Visitor.h"

class Procedure;
class CommandsVisitorBase;

class Command
{
public:
	int get_line_number() const
	{
		return lineNumber;
	}

private:
	int lineNumber;
public:

	explicit Command(int line_number)
		: lineNumber(line_number)
	{
	}

	virtual void accept(CommandsVisitorBase&) const = 0;
	virtual std::string toString(int level = 0) const;
};

class SingleCommand : public Command
{
public:
	explicit SingleCommand(int line_number)
		: Command(line_number)
	{
	}
};

class EmptyCommand : public SingleCommand
{
public:
	explicit EmptyCommand(int line_number)
		: SingleCommand(line_number)
	{
	}

	// Inherited via SingleCommand
	virtual void accept(CommandsVisitorBase&) const override;
};

class SequentialCommand : public Command
{
public:
	SequentialCommand(std::shared_ptr<SingleCommand> command, std::shared_ptr<Command> next_command, int line_number)
		: Command(line_number), command(command),
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
	// Inherited via Command
	void accept(CommandsVisitorBase&) const  override;
	std::string toString(int level) const override;
private:
	std::shared_ptr<SingleCommand> command;
	std::shared_ptr<Command> nextCommand;
	
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

	CallCommand(std::vector<std::shared_ptr<Expression>> parameters, const std::string& target_name, int line_number)
		 : SingleCommand(line_number), parameters(std::move(parameters)),
		   targetName(target_name)
	 {
	 }

	 std::string toString(int level) const override;

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
	explicit DeclareProcedureCommand(std::shared_ptr<Procedure> target, int line_number): SingleCommand(line_number),
	                                                                     target(std::move(target))
	{
	}

	void accept(CommandsVisitorBase&)  const override;
	std::string toString(int level) const override;
};

 class TurtleCommand: public SingleCommand
 {
 public:
	 enum class Type { Left, Right, Forward, Backward };
 private :	
	 Type type;
	 std::shared_ptr<Expression> parameter;
 public: 
	
    TurtleCommand(std::shared_ptr<Expression> parameter, Type type, int line_number)
		 : SingleCommand(line_number), parameter(std::move(parameter)),
		   type(type)
	 {
	 }

    Expression& get_parameter() const
    {
	    return *parameter;
    }

	Type get_type() const
    {
	    return type;
    }

 	void accept(CommandsVisitorBase& v)  const override;
	static std::shared_ptr<TurtleCommand> tryCreate(
		const std::string& identifier, 
		const std::vector<std::shared_ptr<Expression>> &parameter, int line_number)
	{
		 if( identifier == "przod")
		 	return std::make_shared<TurtleCommand>(parameter.front(),Type::Forward, line_number);
		 if (identifier == "tyl")
			 return std::make_shared<TurtleCommand>(parameter.front(), Type::Backward,  line_number);
		 if (identifier == "lewo")
			 return std::make_shared<TurtleCommand>(parameter.front(), Type::Left,  line_number);
		 if (identifier == "prawo")
			 return std::make_shared<TurtleCommand>(parameter.front(), Type::Right, line_number);
		 return std::unique_ptr<TurtleCommand>{};
	}
 };

class IfCommand : public SingleCommand
{	

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

	IfCommand(std::shared_ptr<Expression> condition, std::shared_ptr<Command> body, int line_number)
		: SingleCommand(line_number), condition_(std::move(condition)),
		  body_(std::move(body))
	{
	}

	void accept(CommandsVisitorBase&)  const override;
	std::string toString(int level) const override;
};

class RepeatCommand : public SingleCommand
{

private:
	std::shared_ptr<Expression> count;
	std::shared_ptr<Command> body_;
public:


	const Expression& get_count() const
	{
		return *count;
	}

	const Command& get_body() const
	{
		return *body_;
	}

	RepeatCommand(std::shared_ptr<Expression> count, std::shared_ptr<Command> body, int line_number)
		: SingleCommand(line_number), count(std::move(count)),
		body_(std::move(body))
	{
	}

	void accept(CommandsVisitorBase&)  const override;
	std::string toString(int level) const override;
};

class AssignCommand : public SingleCommand
{
public:
	 std::string get_variable_name() const
	{
		return variableName;
	}

	 std::shared_ptr<Expression> get_initialization_expression() const
	{
		return initializationExpression;
	}

private:
	std::string variableName;
	std::shared_ptr<Expression> initializationExpression;
public:


	AssignCommand( std::string variable_name, std::shared_ptr<Expression> initialization_expression, int line_number)
		: SingleCommand(line_number),
		  variableName(std::move(variable_name)),
		  initializationExpression(std::move(initialization_expression))
	{
	}

	void accept(CommandsVisitorBase&)  const override;
	std::string toString(int level) const override;
};
