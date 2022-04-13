
#include "functions.hpp"

CosNode::CosNode(std::initializer_list<Scalar> const &arguments) : Node(arguments)
{
    if (arguments.size() != 1)
    {
        throw std::invalid_argument("CosNode accepts only 1 argument");
    }
}

std::string CosNode::Type() const
{
    return "CosNode";
}

double CosNode::Value() const
{
    return std::cos(Argument(0)->Value());
}

std::string CosNode::Print() const
{
    return "cos(" + Argument(0)->Print() + ')';
}

std::string CosNode::PrintLaTex() const
{
    return "\\cos(" + Argument(0)->PrintLaTex() + ')';
}

SinNode::SinNode(std::initializer_list<Scalar> const &arguments) : Node(arguments)
{
    if (arguments.size() != 1)
    {
        throw std::invalid_argument("SinNode accepts only 1 argument");
    }
}

std::string SinNode::Type() const
{
    return "SinNode";
}

double SinNode::Value() const
{
    return std::sin(Argument(0)->Value());
}

std::string SinNode::Print() const
{
    return "sin(" + Argument(0)->Print() + ')';
}

std::string SinNode::PrintLaTex() const
{
    return "\\sin(" + Argument(0)->PrintLaTex() + ')';
}

TanNode::TanNode(std::initializer_list<Scalar> const &arguments) : Node(arguments)
{
    if (arguments.size() != 1)
    {
        throw std::invalid_argument("TanNode accepts only 1 argument");
    }
}

std::string TanNode::Type() const
{
    return "TanNode";
}

double TanNode::Value() const
{
    return std::tan(Argument(0)->Value());
}

std::string TanNode::Print() const
{
    return "tan(" + Argument(0)->Print() + ')';
}

std::string TanNode::PrintLaTex() const
{
    return "\\tan(" + Argument(0)->PrintLaTex() + ')';
}

AcosNode::AcosNode(std::initializer_list<Scalar> const &arguments) : Node(arguments)
{
    if (arguments.size() != 1)
    {
        throw std::invalid_argument("AcosNode accepts only 1 argument");
    }
}

std::string AcosNode::Type() const
{
    return "AcosNode";
}

double AcosNode::Value() const
{
    return std::acos(Argument(0)->Value());
}

std::string AcosNode::Print() const
{
    return "acos(" + Argument(0)->Print() + ')';
}

std::string AcosNode::PrintLaTex() const
{
    return "\\arccos(" + Argument(0)->PrintLaTex() + ')';
}

AsinNode::AsinNode(std::initializer_list<Scalar> const &arguments) : Node(arguments)
{
    if (arguments.size() != 1)
    {
        throw std::invalid_argument("AsinNode accepts only 1 argument");
    }
}

std::string AsinNode::Type() const
{
    return "AsinNode";
}

double AsinNode::Value() const
{
    return std::asin(Argument(0)->Value());
}

std::string AsinNode::Print() const
{
    return "asin(" + Argument(0)->Print() + ')';
}

std::string AsinNode::PrintLaTex() const
{
    return "\\arcsin(" + Argument(0)->PrintLaTex() + ')';
}

AtanNode::AtanNode(std::initializer_list<Scalar> const &arguments) : Node(arguments)
{
    if (arguments.size() != 1)
    {
        throw std::invalid_argument("AtanNode accepts only 1 argument");
    }
}

std::string AtanNode::Type() const
{
    return "AtanNode";
}

double AtanNode::Value() const
{
    return std::atan(Argument(0)->Value());
}

std::string AtanNode::Print() const
{
    return "atan(" + Argument(0)->Print() + ')';
}

std::string AtanNode::PrintLaTex() const
{
    return "\\arctan(" + Argument(0)->PrintLaTex() + ')';
}

SqrtNode::SqrtNode(std::initializer_list<Scalar> const &arguments) : Node(arguments)
{
    if (arguments.size() != 1)
    {
        throw std::invalid_argument("SqrtNode accepts only 1 argument");
    }
}

std::string SqrtNode::Type() const
{
    return "SqrtNode";
}

double SqrtNode::Value() const
{
    return std::sqrt(Argument(0)->Value());
}

std::string SqrtNode::Print() const
{
    return "sqrt(" + Argument(0)->Print() + ')';
}

std::string SqrtNode::PrintLaTex() const
{
    return "\\sqrt{" + Argument(0)->PrintLaTex() + '}';
}

AbsNode::AbsNode(std::initializer_list<Scalar> const &arguments) : Node(arguments)
{
    if (arguments.size() != 1)
    {
        throw std::invalid_argument("AbsNode accepts only 1 argument");
    }
}

std::string AbsNode::Type() const
{
    return "AbsNode";
}

double AbsNode::Value() const
{
    return std::abs(Argument(0)->Value());
}

std::string AbsNode::Print() const
{
    return '|' + Argument(0)->Print() + '|';
}

std::string AbsNode::PrintLaTex() const
{
    return "\\left|" + Argument(0)->PrintLaTex() + "\\right|";
}

ExpNode::ExpNode(std::initializer_list<Scalar> const &arguments) : Node(arguments)
{
    if (arguments.size() != 1)
    {
        throw std::invalid_argument("ExpNode accepts only 1 argument");
    }
}

std::string ExpNode::Type() const
{
    return "ExpNode";
}

double ExpNode::Value() const
{
    return std::exp(Argument(0)->Value());
}

std::string ExpNode::Print() const
{
    std::string a = Argument(0)->Print();
    return "e^" + Node::Out(a);
}

std::string ExpNode::PrintLaTex() const
{
    return "\\exp(" + Argument(0)->PrintLaTex() + ')';
}

LnNode::LnNode(std::initializer_list<Scalar> const &arguments) : Node(arguments)
{
    if (arguments.size() != 1)
    {
        throw std::invalid_argument("LnNode accepts only 1 argument");
    }
}

std::string LnNode::Type() const
{
    return "LnNode";
}

double LnNode::Value() const
{
    return std::log(Argument(0)->Value());
}

std::string LnNode::Print() const
{
    return "ln(" + Argument(0)->Print() + ')';
}

std::string LnNode::PrintLaTex() const
{
    return "\\ln(" + Argument(0)->PrintLaTex() + ')';
}