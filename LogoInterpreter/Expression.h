#pragma once
#include <memory>
#include <string>

class Token;
class CommandsEnvironment;

class Expression
{
public:
	virtual ~Expression() = default;
	virtual double evaluate(const CommandsEnvironment&) const = 0;
		
};

class OperatorExpression : public Expression
{
protected:
	std::shared_ptr<Expression> leftOperand;
	std::shared_ptr<Expression> rightOperand;
	int priority;
public:


	OperatorExpression(std::shared_ptr<Expression> left_operand,
		std::shared_ptr<Expression> right_operand)
		: leftOperand(std::move(left_operand)),
		  rightOperand(std::move(right_operand))
	{
	}

	static std::shared_ptr<OperatorExpression> tryCreateFromToken(const Token& token, 
		const std::shared_ptr<Expression>& oper1, const std::shared_ptr<Expression>& oper2);
};

class OperatorDiv : public OperatorExpression
{
public:

	OperatorDiv(std::shared_ptr<Expression> left_operand, std::shared_ptr<Expression> right_operand)
		: OperatorExpression(std::move(left_operand), std::move(right_operand))
	{
	}

	double evaluate(const CommandsEnvironment&) const override;
};

class OperatorAdd : public OperatorExpression
{
public:


	OperatorAdd(std::shared_ptr<Expression> left_operand, std::shared_ptr<Expression> right_operand)
		: OperatorExpression(std::move(left_operand), std::move(right_operand))
	{
	}

	double evaluate(const CommandsEnvironment&) const override;
};

class OperatorMul : public OperatorExpression
{
public:


	OperatorMul(std::shared_ptr<Expression> left_operand, std::shared_ptr<Expression> right_operand)
		: OperatorExpression(std::move(left_operand), std::move(right_operand))
	{
	}

	double evaluate(const CommandsEnvironment&) const override;
};
class OperatorSub : public OperatorExpression
{
public:


	OperatorSub(std::shared_ptr<Expression> left_operand, std::shared_ptr<Expression> right_operand)
		: OperatorExpression(std::move(left_operand), std::move(right_operand))
	{
	}

	double evaluate(const CommandsEnvironment&) const override;
};

class OperatorGreater : public OperatorExpression
{
public:


	OperatorGreater(std::shared_ptr<Expression> left_operand, std::shared_ptr<Expression> right_operand)
		: OperatorExpression(std::move(left_operand), std::move(right_operand))
	{
	}

	double evaluate(const CommandsEnvironment& e) const override;
};

class OperatorGreaterEqual : public OperatorExpression
{
public:


	OperatorGreaterEqual(std::shared_ptr<Expression> left_operand, std::shared_ptr<Expression> right_operand)
		: OperatorExpression(std::move(left_operand), std::move(right_operand))
	{
	}

	double evaluate(const CommandsEnvironment& e) const override;
};
class OperatorLess : public OperatorExpression
{
public:


	OperatorLess(std::shared_ptr<Expression> left_operand, std::shared_ptr<Expression> right_operand)
		: OperatorExpression(std::move(left_operand), std::move(right_operand))
	{
	}

	double evaluate(const CommandsEnvironment& e) const override;
};
class OperatorEqual : public OperatorExpression
{
public:


	OperatorEqual(std::shared_ptr<Expression> left_operand, std::shared_ptr<Expression> right_operand)
		: OperatorExpression(std::move(left_operand), std::move(right_operand))
	{
	}

	double evaluate(const CommandsEnvironment& e) const override;
};
class OperatorNotEqual : public OperatorExpression
{
public:


	OperatorNotEqual(std::shared_ptr<Expression> left_operand, std::shared_ptr<Expression> right_operand)
		: OperatorExpression(std::move(left_operand), std::move(right_operand))
	{
	}

	double evaluate(const CommandsEnvironment& e) const override;
};

class ConstantExpresion : public Expression
{
public:
	explicit ConstantExpresion(double value)
		: value(value)
	{
	}

	virtual double evaluate(const CommandsEnvironment&) const override;
private:
	double value;

};
class VarExpression : public Expression
{
private:
	std::string name;
public:
	virtual double evaluate(const CommandsEnvironment&) const override;


	explicit VarExpression(const std::string& name)
		: name(name)
	{
	}

	std::string get_name() const
	{
		return name;
	}
};
