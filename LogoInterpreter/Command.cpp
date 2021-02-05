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

void DeclareFunctionCommand::accept(CommandsVisitorBase& v)
{
	v.onVisit(*this);
}

