
#include <iostream>

#include "Command.h"
#include "Parser.h"
#include "Token.h"
#include "Visitor.h"


using namespace std;

void main()
{
	vector<shared_ptr<Token>> tokens;	
	
	//
	//  tokens.push_back(make_shared<Token>("foo", TokenType::Identifier));
	//  tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
	//  tokens.push_back(make_shared<Token>("x", TokenType::Identifier));
	//  tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));
	//
	// tokens.push_back(make_shared<Token>("przod", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
	// tokens.push_back(make_shared<Token>("x", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));
	// tokens.push_back(make_shared<Token>(";", TokenType::Semicolon));
	// tokens.push_back(make_shared<Token>("przod", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
	// tokens.push_back(make_shared<Token>("x", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));
	// tokens.push_back(make_shared<Token>(";", TokenType::Semicolon));
	// tokens.push_back(make_shared<Token>("end", TokenType::EndBlock));
	//
	// tokens.push_back(make_shared<Token>("foo", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
	// tokens.push_back(make_shared<Token>("3", TokenType::Number));
	// tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));
	// tokens.push_back(make_shared<Token>(";", TokenType::Semicolon));
	


  tokens.push_back(make_shared<Token>("foo", TokenType::Identifier));
  tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
  tokens.push_back(make_shared<Token>("x", TokenType::Identifier));
  tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));


  tokens.push_back(make_shared<Token>("przod", TokenType::Identifier));
  tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
  tokens.push_back(make_shared<Token>("x", TokenType::Identifier));
  tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));
  tokens.push_back(make_shared<Token>(";", TokenType::Semicolon));

	
	tokens.push_back(make_shared<Token>("if", TokenType::IfKeyword));
	tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
	tokens.push_back(make_shared<Token>("3", TokenType::Number));
	tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));
		
	tokens.push_back(make_shared<Token>("foo", TokenType::Identifier));
	tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
	tokens.push_back(make_shared<Token>("x", TokenType::Identifier));
	tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));
	tokens.push_back(make_shared<Token>(";", TokenType::Semicolon));
	
	tokens.push_back(make_shared<Token>("end", TokenType::EndBlock));
	//
	// tokens.push_back(make_shared<Token>("przod", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
	// tokens.push_back(make_shared<Token>("x", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));
	// tokens.push_back(make_shared<Token>(";", TokenType::Semicolon));
	
	tokens.push_back(make_shared<Token>("end", TokenType::EndBlock));

	 tokens.push_back(make_shared<Token>("foo", TokenType::Identifier));
	 tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
	 tokens.push_back(make_shared<Token>("3", TokenType::Number));
	 tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));
	 tokens.push_back(make_shared<Token>(";", TokenType::Semicolon));
	//tokens.push_back(make_shared<Token>("end", TokenType::EndBlock));

	
	
	CommandsVisitor visitor;
	try
	{
		Parser p(tokens);
		auto program = p.parse();
		program->accept(visitor);	
	}
	catch (runtime_error& e)
	{
		cout << e.what();
	}
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
	
}