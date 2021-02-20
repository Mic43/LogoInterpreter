#pragma once

#include <map>
#include "Commands.h"
#include "CommandsEnvironment.h"

class CommandsVisitorBase
{
public:
	//virtual void onVisit(const Command& command) = 0;	
	virtual void onVisit(const SequentialCommand& ) = 0;
	virtual void onVisit(const EmptyCommand&) = 0;
	virtual void onVisit(const CallCommand& call_command) = 0;
	virtual void onVisit(const DeclareProcedureCommand& call_command) = 0;
	virtual void onVisit(const TurtleCommand& turtle_command) = 0;
	virtual void onVisit(const IfCommand& if_command) = 0;
	virtual void onVisit(const RepeatCommand& repeat_command) = 0;
	virtual void onVisit(const AssignCommand& assign_command) = 0;
};


class CommandsVisitor : public CommandsVisitorBase
{
private:
	CommandsEnvironment environment;
	void throwExecutionError(const std::string& message, const Command& command) const;

public:

	explicit CommandsVisitor(const CommandsEnvironment& environment)
		: environment(environment)
	{
	}
	explicit CommandsVisitor(std::shared_ptr<TurtleState> turtleState)
		: environment(CommandsEnvironment(turtleState))
	{
	}

	CommandsEnvironment get_environment() const
	{
		return environment;
	}

	// Inherited via VisitorBase	

	void onVisit(const EmptyCommand&) override;
	void onVisit(const SequentialCommand& ) override;
	void onVisit(const CallCommand& call_command) override;
	void onVisit(const DeclareProcedureCommand& call_command) override;
	void onVisit(const TurtleCommand& turtle_command) override;
	void onVisit(const IfCommand& if_command) override;
	void onVisit(const RepeatCommand& repeat_command) override;
	void onVisit(const AssignCommand& assign_command) override;

	static CommandsVisitor createNestedVisitor(const CommandsEnvironment& nestedEnvironment);
};

