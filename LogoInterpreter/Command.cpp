#include "Command.h"
#include <iostream>
#include "Visitor.h"

using namespace std;


void SequentialCommand::accept(CommandsVisitorBase& v)
{
	v.onVisit(*this);
}

void EmptyCommand::accept(CommandsVisitorBase& v)
{
	v.onVisit(*this);
}

void CallCommand::accept(CommandsVisitorBase& v)
{
	v.onVisit(*this);
}

void DeclareProcedureCommand::accept(CommandsVisitorBase& v)
{
	v.onVisit(*this);
}

void TurtleCommand::accept(CommandsVisitorBase& v)
{
	v.onVisit(*this);
}

void IfCommand::accept(CommandsVisitorBase& v)
{
	v.onVisit(*this);

}

