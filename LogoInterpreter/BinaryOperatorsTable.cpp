#include "BinaryOperatorsTable.h"
#include "Expression.h"
#include <algorithm>
const std::map<std::string, BinaryOperatorsTable::OperatorExpressionCreator> BinaryOperatorsTable::symbolMapping =
{
	{"+", [](auto oper1,auto oper2) {return std::make_shared<OperatorAdd>(oper1, oper2); }},
	{"-", [](auto oper1,auto oper2) {return std::make_shared<OperatorSub>(oper1, oper2); }},
	{"*", [](auto oper1,auto oper2) {return std::make_shared<OperatorMul>(oper1, oper2); }},
	{"/", [](auto oper1,auto oper2) {return std::make_shared<OperatorDiv>(oper1, oper2); }},
	{"=", [](auto oper1,auto oper2) {return std::make_shared<OperatorEqual>(oper1, oper2); }},
	{">", [](auto oper1,auto oper2) {return std::make_shared<OperatorGreater>(oper1, oper2); }},
	{">=", [](auto oper1,auto oper2) {return std::make_shared<OperatorGreaterEqual>(oper1, oper2); }},
	{"<", [](auto oper1,auto oper2) {return std::make_shared<OperatorLess>(oper1, oper2); }},
	{"<>", [](auto oper1,auto oper2) {return std::make_shared<OperatorNotEqual>(oper1, oper2); }},
};


const std::map<TokenType, int> BinaryOperatorsTable::precedenceTable =
{
	{TokenType::OperatorEqual,1},
	{TokenType::OperatorNotEqual,1},
	{TokenType::OperatorLess,3},
	{TokenType::OperatorLessEqual,3},
	{TokenType::OperatorGreater,3},
	{TokenType::OperatorGreaterEqual,3},
	{TokenType::OperatorPlus,3},
	{TokenType::OperatorMinus,3},
	{TokenType::OperatorMul,4},
	{TokenType::OperatorDiv,4},

};
std::shared_ptr<OperatorExpression> BinaryOperatorsTable::tryCreateOperatorExpression(
	std::string symbol, 
	std::shared_ptr<Expression> par1,
	std::shared_ptr<Expression> par2)
{
	auto res = symbolMapping.find(symbol);
	if (res == symbolMapping.end())
		return std::shared_ptr<OperatorExpression>();
	return (*res).second(par1,par2);
}

bool BinaryOperatorsTable::isOperatorSymbol(char c)
{
	return std::any_of(symbolMapping.begin(), symbolMapping.end(), 
		[&c](auto entry) {return entry.first.find(c) != std::string::npos; });
}

bool BinaryOperatorsTable::isBinaryOperator(TokenType token)
{
	return precedenceTable.find(token) != precedenceTable.end();
}

int BinaryOperatorsTable::getPrecedence(TokenType token)
{
	return precedenceTable.find(token)->second;
}
