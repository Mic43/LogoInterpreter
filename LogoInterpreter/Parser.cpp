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
		throwParsingError("badly formed parameter list");
	}
}

std::shared_ptr<Expression> Parser::parseOperator(const Token& oper,
	const Token& operand1, const Token& operand2) const
{
	auto op1Exp = parseValue(operand1);
	auto op2Exp = parseValue(operand2);

	return OperatorExpression::tryCreateFromToken(oper, op1Exp, op2Exp);
}

std::shared_ptr<Expression> Parser::parseExpression(std::vector<Token>::iterator& token, bool& endReached)
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
	throwParsingError("badly formed expression");
}

std::vector<shared_ptr<Expression>> Parser::parseParameterList(std::vector<Token>::iterator& token)
{
	assumeNotEnd(token);
	if (token->get_type() != TokenType::OpenPar)	
		throwParsingError("badly formed parameter list");

	++token;

	vector<shared_ptr<Expression>> res;
	bool end_reached = false;
	while (token != tokens.end() && !end_reached)
	{
		res.push_back(parseExpression(token, end_reached));
	}
	return res;
}

void Parser::assumeNotEnd(std::vector<Token>::iterator& token)
{
	if (isEnd(token))
		throwParsingError("Unexpected end of file");
}

std::shared_ptr<Command> Parser::parse()
{
	auto token = tokens.begin();
	currentLineNumber = 1;
	return parse(token,"");
}

void Parser::throwParsingError(const string& message) const
{
	throw runtime_error(message + ", line: " + std::to_string(currentLineNumber));
}

shared_ptr<Command> Parser::parse(vector<Token>::iterator& token, string blockName)
{
	if (isEnd(token))
		return std::make_shared<EmptyCommand>(currentLineNumber);

	const Token& current = *token;

	shared_ptr<SingleCommand> currentCommand;
	switch (current.get_type())
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
			auto tc = TurtleCommand::tryCreate(name, parameters,currentLineNumber);

			if (!tc)
				currentCommand = std::make_shared<CallCommand>(CallCommand(parameters, name, currentLineNumber));
			else
				currentCommand = tc;

			break;
		}

		// handle procedure declaration
		vector<string> paramNames(parameters.size());
		std::transform(parameters.begin(), parameters.end(), paramNames.begin(),
			[this](auto exp)
			{
				std::shared_ptr<VarExpression> varExp = std::dynamic_pointer_cast<VarExpression>(exp);
				if (varExp)
				{
					return varExp->get_name();
				}
				throwParsingError("error parsing procedure definition");			
			});
		int curLineNumberTemp = currentLineNumber;
		auto body = parse(token, name);
		currentCommand = std::make_shared<DeclareProcedureCommand>(
			std::make_shared<Procedure>(paramNames, name, body), 
			curLineNumberTemp);
		break;
	}
	case TokenType::IfKeyword:
	{
		++token;
		int curLineNumberTemp = currentLineNumber;
		assumeNotEnd(token);
		if (token->get_type() != TokenType::OpenPar)
			throwParsingError("expected condition");


		bool end;
		auto expression = parseExpression(++token, end);
		if (!end)			
			throwParsingError("malformed if condition");

		auto body = parse(token, "if");
		currentCommand = make_shared<IfCommand>(expression, body, curLineNumberTemp);
		break;
	}
	case TokenType::Semicolon:
		currentCommand = std::make_shared<EmptyCommand>(currentLineNumber);
		++token;
		break;
	case TokenType::EndLine:
		currentLineNumber++;
		return parse(++token, blockName);// = std::make_shared<EmptyCommand>();		 			
	case TokenType::EndBlock:
		if ((++token)->get_content() != blockName)			
			throwParsingError("malformed end block");

		if ((++token)->get_type() != TokenType::Semicolon)						
			throwParsingError("malformed end block");

		++token;
		return std::make_shared<EmptyCommand>(currentLineNumber);
	case TokenType::OpenPar:
	case TokenType::ClosePar:
	case TokenType::Number:
	case TokenType::Comma:
	case TokenType::Operator:
		throwParsingError("Symbol not expected");
	default:
		throwParsingError("Not recognized token type");		
	}

	auto nextCommand = parse(token, blockName);
	return std::make_shared<SequentialCommand>(currentCommand, nextCommand, currentLineNumber);
}
