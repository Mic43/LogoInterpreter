#include "Parser.h"
#include "Token.h"
#include <algorithm>
#include <stack>
#include <stdexcept>
#include "CommandsEnvironment.h"
#include <string>

using namespace std;

std::shared_ptr<Expression> Parser::parseValue(const Token& token) const
{	
	switch (token.get_type())
	{
	case TokenType::Identifier:
		return (make_shared<VarExpression>(token.get_content()));
	case TokenType::Number:
		return make_shared<ConstantExpresion>(stod(token.get_content()));
	default:
		throw runtime_error("badly formed parameter list");
	}
}

std::shared_ptr<Expression> Parser::parseOperator(const Token& oper,
	const Token& operand1, const Token& operand2) const
{
	auto op1Exp = parseValue(operand1);
	auto op2Exp = parseValue(operand2);

	return OperatorExpression::tryCreateFromToken(oper, op1Exp, op2Exp);
}

std::shared_ptr<Expression> Parser::parseExpression(std::vector<Token>::iterator& token,bool& endReached)
{
	stack<Token> stack;

	while (token != tokens.end() && token->get_type() != TokenType::Comma && token->get_type() != TokenType::ClosePar)
	{
		stack.push(*token);
		++token;
	}
	assumeNotEnd(token);
	endReached = token->get_type() == TokenType::ClosePar;
	++token;
	if (stack.size() == 1)
	{		
		return parseValue(stack.top());
	}
	if (stack.size() == 3)
	{
		auto operand2 = stack.top(); stack.pop();
		auto oper = stack.top(); stack.pop();
		auto operand1 = stack.top(); stack.pop();

		return parseOperator(oper, operand1, operand2);
	}
	throw runtime_error("badly formed expression");
}

std::vector<shared_ptr<Expression>> Parser::parseParameterList(std::vector<Token>::iterator& token)
{
	assumeNotEnd(token);
	if (token->get_type() != TokenType::OpenPar)
		throw runtime_error("badly formed parameter list");
	++token;
	
	vector<shared_ptr<Expression>> res;
	bool end_reached = false;
	while(token != tokens.end() && !end_reached)
	{		
		res.push_back(parseExpression(token, end_reached));			
	}
	return res;
}

void Parser::assumeNotEnd(std::vector<Token>::iterator& token)
{
	if (isEnd(token))
		throw std::runtime_error("unexpected end of file");
}

std::shared_ptr<Command> Parser::parse()
{
	auto token = tokens.begin();
	return parse(token);
}

shared_ptr<Command> Parser::parse(vector<Token>::iterator& token,string blockName)
{
	if (isEnd(token))
		return std::make_shared<EmptyCommand>();
	
	const Token& current = *token;
	
	shared_ptr<SingleCommand> currentCommand;
	switch(current.get_type())
	{
		case TokenType::Identifier:
		{
		 	
		 	 string name = token->get_content();
		 	 vector<shared_ptr<Expression>> parameters = parseParameterList(++token);			
			 assumeNotEnd(token);
			 
		 	 // handle call
		 	 if (token->get_type() == TokenType::Semicolon)
		 	 {
		 	 	++token;
		 	 	auto tc = TurtleCommand::tryCreate(name, parameters);
		 	
		 	 	if (!tc)									
					currentCommand =  std::make_shared<CallCommand>(CallCommand(parameters, name));
		 	 	else
					currentCommand = tc;
		 	 	
		 	 	break;
		 	 }
			 
		 	 // handle procedure declaration
		 	 vector<string> paramNames(parameters.size());
		 	 std::transform(parameters.begin(), parameters.end(), paramNames.begin(), 
		 	 	[](auto exp)
		 	 	{
		 	 		std::shared_ptr<VarExpression> varExp = std::dynamic_pointer_cast<VarExpression>(exp);
		 	 		if (varExp)
		 	 		{
		 	 			return varExp->get_name();
		 	 		}
		 	 		throw runtime_error("error parsing procedure definition");
		 	 	});
			 
		 	 auto body = parse(token,name);
			 currentCommand = std::make_shared<DeclareProcedureCommand>(std::make_shared<Procedure>(paramNames, name, body));
		 	 break;
		}
		case TokenType::IfKeyword:
		{
		 	 ++token;
			 
			 assumeNotEnd(token);
		 	 if (token->get_type() != TokenType::OpenPar)
		 	 	throw runtime_error("expected condition");
			 
		 	 bool end;
		 	 auto expression = parseExpression(++token,end);
		 	 if (!end)
		 	 	throw runtime_error("malformed if condition");
		 	 auto body = parse(token,"if");
			 currentCommand = make_shared<IfCommand>(expression, body);
		 	 break;
		}		
		case TokenType::Semicolon:
			currentCommand = std::make_shared<EmptyCommand>();
		 	++token;
		 	break;
		case TokenType::EndLine:
		 	return parse(++token,blockName);// = std::make_shared<EmptyCommand>();		 	
		 	//break;
		case TokenType::EndBlock:				
				if ((++token)->get_content() != blockName)
					throw runtime_error("malformed end block");				
				if ((++token)->get_type() != TokenType::Semicolon)
					throw runtime_error("malformed end block");
				++token;				
			return std::make_shared<EmptyCommand>();
		case TokenType::OpenPar: 
		case TokenType::ClosePar: 
		case TokenType::Number: 
		case TokenType::Comma: 		
		case TokenType::Operator:
		 	throw runtime_error("Symbol not expected");
		default:
		 	throw runtime_error("Not recognized token type");
	 }

	auto nextCommand = parse(token, blockName);
	return std::make_shared<SequentialCommand>(currentCommand, nextCommand);
}
	
	
	//shared_ptr<Command> res = make_shared<EmptyCommand>();
	// if (token == tokens.end())
	// 	return make_shared <EmptyCommand> ();
	//
	// shared_ptr<SingleCommand> res;
	// 	
	// switch (token->get_type())
	// {		
	// 	case TokenType::Identifier:
	// 	{
	// 		
	// 		string name = token->get_content();
	// 		vector<shared_ptr<Expression>> parameters = parseParameterList(++token);			
	// 		assumeNotLast(token);
	//
	// 		// handle call
	// 		if (token->get_type() == TokenType::Semicolon)
	// 		{
	// 			++token;
	// 			auto tc = TurtleCommand::tryCreate(name, parameters);
	// 		
	// 			if (!tc)									
	// 				res =  std::make_shared<CallCommand>(CallCommand(parameters, name));				
	// 			else
	// 				res = tc;
	// 			
	// 			break;
	// 		}
	//
	// 		// handle procedure declaration
	// 		vector<string> paramNames(parameters.size());
	// 		std::transform(parameters.begin(), parameters.end(), paramNames.begin(), 
	// 			[](auto exp)
	// 			{
	// 				std::shared_ptr<VarExpression> varExp = std::dynamic_pointer_cast<VarExpression>(exp);
	// 				if (varExp)
	// 				{
	// 					return varExp->get_name();
	// 				}
	// 				throw runtime_error("error parsing procedure definition");
	// 			});
	//
	// 		auto body = parse(token,name);
	// 		res = std::make_shared<DeclareProcedureCommand>(std::make_shared<Procedure>(paramNames, name, body));
	// 		break;
	// 	}
	// 	case TokenType::IfKeyword:
	// 	{
	// 		++token;
	//
	// 		assumeNotLast(token);
	// 		if (token->get_type() != TokenType::OpenPar)
	// 			throw runtime_error("expected condition");
	//
	// 		bool end;
	// 		auto expression = parseExpression(++token,end);
	// 		if (!end)
	// 			throw runtime_error("malformed if condition");
	// 		auto body = parse(token,"if");
	// 		res = make_shared<IfCommand>(expression, body);
	// 		break;
	// 	}		
	// 	case TokenType::Semicolon:
	// 		res = std::make_shared<EmptyCommand>();
	// 		++token;
	// 		break;
	// 	case TokenType::EndLine:
	// 		return parse(++token);// = std::make_shared<EmptyCommand>();
	// 		//++token;
	// 		//break;
	// 	case TokenType::EndBlock:		
	// 	case TokenType::OpenPar: 
	// 	case TokenType::ClosePar: 
	// 	case TokenType::Number: 
	// 	case TokenType::Comma: 		
	// 	case TokenType::Operator:
	// 		throw runtime_error("Symbol not expected");
	// 	default:
	// 		throw runtime_error("Not recognized token type");
	// }
	//
	// if (token == tokens.end())
	// 	return res;
	// if (token->get_type() == TokenType::EndBlock)
	// {
	// 	assumeNotLast(token);
	// 	if ((++token)->get_content() != blockName)
	// 		throw runtime_error("malformed end block");
	// 	assumeNotLast(token);
	// 	if ((++token)->get_type() != TokenType::Semicolon)
	// 		throw runtime_error("malformed end block");
	// 	++token;
	// 	return res;
	// }

	
	//return std::make_shared<SequentialCommand>(res, parse(token,blockName));
//}
