
#include "operations.hpp"

ExponentiationNode::ExponentiationNode(std::initializer_list<Scalar> const &arguments) : Node(arguments)
{
    if (arguments.size() != 2)
    {
        throw std::invalid_argument("ExponentiationNode accepts only 2 arguments");
    }
}

std::string ExponentiationNode::Type() const
{
    return "ExponentiationNode";
}

double ExponentiationNode::Value() const
{
    return std::pow(Argument(0)->Value(), Argument(1)->Value());
}

MultiplicationNode::MultiplicationNode(std::initializer_list<Scalar> const &arguments) : Node(arguments)
{
    if (arguments.size() != 2)
    {
        throw std::invalid_argument("MultiplicationNode accepts only 2 arguments");
    }
}

std::string MultiplicationNode::Type() const
{
    return "MultiplicationNode";
}

double MultiplicationNode::Value() const
{
    return Argument(0)->Value() * Argument(1)->Value();
}

DivisionNode::DivisionNode(std::initializer_list<Scalar> const &arguments) : Node(arguments)
{
    if (arguments.size() != 2)
    {
        throw std::invalid_argument("DivisionNode accepts only 2 arguments");
    }
}

std::string DivisionNode::Type() const
{
    return "DivisionNode";
}

double DivisionNode::Value() const
{
    return Argument(0)->Value() / Argument(1)->Value();
}

AdditionNode::AdditionNode(std::initializer_list<Scalar> const &arguments) : Node(arguments)
{
    if (arguments.size() != 2)
    {
        throw std::invalid_argument("AdditionNode accepts only 2 arguments");
    }
}

std::string AdditionNode::Type() const
{
    return "AdditionNode";
}

double AdditionNode::Value() const
{
    return Argument(0)->Value() + Argument(1)->Value();
}

SubtractionNode::SubtractionNode(std::initializer_list<Scalar> const &arguments) : Node(arguments)
{
    if (arguments.size() != 2)
    {
        throw std::invalid_argument("SubtractionNode accepts only 2 arguments");
    }
}

std::string SubtractionNode::Type() const
{
    return "SubtractionNode";
}

double SubtractionNode::Value() const
{
    return Argument(0)->Value() - Argument(1)->Value();
}
