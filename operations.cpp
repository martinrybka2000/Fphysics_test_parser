
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

std::string ExponentiationNode::Print() const
{
    std::string a = Argument(0)->Print();
    std::string b = Argument(1)->Print();

    return Node::Out(a) + '^' + Node::Out(b);
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

std::string MultiplicationNode::Print() const
{
    std::string a = Argument(0)->Print();
    std::string b = Argument(1)->Print();

    return Node::Out(a) + '*' + Node::Out(b);
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

std::string DivisionNode::Print() const
{
    std::string a = Argument(0)->Print();
    std::string b = Argument(1)->Print();

    return Node::Out(a) + '/' + Node::Out(b);
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

std::string AdditionNode::Print() const
{
    std::string a = Argument(0)->Print();
    std::string b = Argument(1)->Print();

    return Node::Out(a) + '+' + Node::Out(b);
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

std::string SubtractionNode::Print() const
{
    std::string a = Argument(0)->Print();
    std::string b = Argument(1)->Print();

    return Node::Out(a) + '-' + Node::Out(b);
}