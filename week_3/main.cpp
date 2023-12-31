#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

class ExpressionValue : public Expression
{
public:
    ExpressionValue(int value) : value_(value) {}

    virtual int Evaluate() const override
    {
        return value_;
    }
    virtual string ToString() const override
    {
        return to_string(value_);
    }

private:
    int value_;
};

class ExpressionOperator : public Expression
{
public:
    ExpressionOperator(ExpressionPtr left, ExpressionPtr right) : left_(move(left)), right_(move(right)) {}

    virtual int Evaluate() const final
    {
        return EvaluateOperator(left_->Evaluate(), right_->Evaluate());
    }
    virtual string ToString() const final
    {
        ostringstream result;
        result << '(' << left_->ToString() << ')' << OperatorChar() << '(' << right_->ToString() << ')';
        return result.str();
    }

private:
    virtual int EvaluateOperator(int left_value, int right_value) const = 0;
    virtual char OperatorChar() const = 0;

    ExpressionPtr left_;
    ExpressionPtr right_;
};

class ExpressionSum : public ExpressionOperator
{
public:
    using ExpressionOperator::ExpressionOperator;

private:
    virtual int EvaluateOperator(int left_value, int right_value) const final
    {
        return left_value + right_value;
    }

    virtual char OperatorChar() const final
    {
        return '+';
    }
};

class ExpressionProduct : public ExpressionOperator
{
public:
    using ExpressionOperator::ExpressionOperator;

private:
    virtual int EvaluateOperator(int left_value, int right_value) const final
    {
        return left_value * right_value;
    }

    virtual char OperatorChar() const final
    {
        return '*';
    }
};

ExpressionPtr Value(int value)
{
    return make_unique<ExpressionValue>(value);
}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right)
{
    return make_unique<ExpressionSum>(move(left), move(right));
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right)
{
    return make_unique<ExpressionProduct>(move(left), move(right));
}

string Print(const Expression *e)
{
    if (!e)
    {
        return "Null expression provided";
    }
    stringstream output;
    output << e->ToString() << " = " << e->Evaluate();
    return output.str();
}

void Test()
{
    ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
    ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

    ExpressionPtr e2 = Sum(move(e1), Value(5));
    ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

    ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, Test);
    return 0;
}
