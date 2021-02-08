
#include <iostream>

#include "Command.h"
#include "Parser.h"
#include "Token.h"
#include "Visitor.h"


using namespace std;

void main()
{
	vector<Token*> tokens;
	auto semi = make_shared<Token>(";", TokenType::Semicolon);
	tokens.push_back(semi.get());
	tokens.push_back(semi.get());
	tokens.push_back(semi.get());

	Parser p(tokens);
	auto res = p.parse();
	
	CommandsVisitor visitor;
	(*res).accept(visitor);
	// EmptyCommand empty;
	//
	// const char* procName = "foo";	
	// vector<string> params{ "k" };
	//
	// VarExpresion var (params[0]);
	//
	// TurtleCommand turtleCmd(&var,TurtleCommand::Direction::Left);
	// vector<Expression*> v2{ &var };
	// CallCommand call2(v2, procName);
	// SequentialCommand s(&turtleCmd, &call2);
	// Command* body = &s;
	//
	//
	// ConstantExpresion constant(10);
	// vector<Expression*> v{ &constant };
	// CallCommand call(v, procName);
	//
	// Procedure p(params, procName, body);
	// DeclareProcedureCommand procedure_command(&p);
	//
	//
	// auto cmd = SequentialCommand(&procedure_command, &call);
	// Command& program = cmd;
	//
	// program.accept(visitor);
	// cout << visitor.get_environment().get_turtle_state()->get_state();
	// try
	// {
	// 	program.accept(visitor);	
	// }
	// catch (runtime_error& e)
	// {
	// 	cout << e.what();
	// }
}