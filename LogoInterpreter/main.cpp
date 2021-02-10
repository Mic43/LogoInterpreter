
#include <iostream>

#include "Command.h"
#include "Parser.h"
#include "Scanner.h"
#include "Token.h"
#include "Visitor.h"


using namespace std;

void main()
{
	//vector<shared_ptr<Token>> tokens;

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



	// tokens.push_back(make_shared<Token>("foo", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
	// tokens.push_back(make_shared<Token>("x", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>(",", TokenType::Comma));
	// tokens.push_back(make_shared<Token>("y", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));
	//
	//
	// tokens.push_back(make_shared<Token>("przod", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
	// tokens.push_back(make_shared<Token>("x", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>("+", TokenType::Operator));
	// tokens.push_back(make_shared<Token>("y", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));
	// tokens.push_back(make_shared<Token>(";", TokenType::Semicolon));
	//
	//
	// tokens.push_back(make_shared<Token>("if", TokenType::IfKeyword));
	// tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
	// tokens.push_back(make_shared<Token>("x", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>(">", TokenType::Operator));
	// tokens.push_back(make_shared<Token>("0", TokenType::Number));
	//
	// tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));
	//
	// tokens.push_back(make_shared<Token>("foo", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
	// tokens.push_back(make_shared<Token>("x", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>("-", TokenType::Operator));
	// tokens.push_back(make_shared<Token>("1", TokenType::Number));
	// tokens.push_back(make_shared<Token>(",", TokenType::Comma));
	// tokens.push_back(make_shared<Token>("x", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));
	// tokens.push_back(make_shared<Token>(";", TokenType::Semicolon));
	//
	// tokens.push_back(make_shared<Token>("end", TokenType::EndBlock));
	// //
	//
	//
	// tokens.push_back(make_shared<Token>("end", TokenType::EndBlock));
	//
	// tokens.push_back(make_shared<Token>("foo", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
	// tokens.push_back(make_shared<Token>("5", TokenType::Number));
	// tokens.push_back(make_shared<Token>(",", TokenType::Comma));
	// tokens.push_back(make_shared<Token>("3", TokenType::Number));
	// tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));
	// tokens.push_back(make_shared<Token>(";", TokenType::Semicolon));
	// //
	// tokens.push_back(make_shared<Token>("przod", TokenType::Identifier));
	// tokens.push_back(make_shared<Token>("(", TokenType::OpenPar));
	// tokens.push_back(make_shared<Token>("5", TokenType::Number));
	// tokens.push_back(make_shared<Token>(")", TokenType::ClosePar));
	// tokens.push_back(make_shared<Token>(";", TokenType::Semicolon));
   //tokens.push_back(make_shared<Token>("end", TokenType::EndBlock));

	string input = "foo(x,n) if (n > 0) przod(x); lewo(45);foo(x*0.75,n-1);prawo(90);;foo(x*0.75,n-1);lewo(45);tyl(x);end;end; foo(20,3);";

	//string input = "przod(3);prawo(45);przod(10);lewo(135);przod(4);";

	int boardSize = 100;
	CommandsVisitor visitor(std::make_shared<TurtleState>(boardSize));
	try
	{
		Scanner s(input);
		auto tokens = s.tokenize();
		
		Parser p(tokens);
		auto program = p.parse();
		program->accept(visitor);
	}
	catch (runtime_error& e)
	{
		cout << e.what();
	}
	auto turtle_state = visitor.get_environment().get_turtle_state();
	
	for (int i = 0; i < turtle_state->get_board_size(); ++i)
	{
		for (int j = 0; j < turtle_state->get_board_size(); ++j)
		{
			cout << (turtle_state->getState(j,i) ? "*" : " ");
		}
		cout << endl;
	}		
}