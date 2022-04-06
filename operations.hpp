
#pragma once

#include <memory>
#include <cmath>
#include <iostream>

#include "node.hpp"

class AdditionNode : public Node
{
public:
    AdditionNode(std::initializer_list<Scalar> const &arguments);

    std::string Type() const override;

    double Value() const override;
};

class SubtractionNode : public Node
{
public:
    SubtractionNode(std::initializer_list<Scalar> const &arguments);

    std::string Type() const override;

    double Value() const override;
};

class MultiplicationNode : public Node
{
public:
    MultiplicationNode(std::initializer_list<Scalar> const &arguments);

    std::string Type() const override;

    double Value() const override;
};

class DivisionNode : public Node
{
public:
    DivisionNode(std::initializer_list<Scalar> const &arguments);

    std::string Type() const override;

    double Value() const override;
};

class ExponentiationNode : public Node
{
public:
    ExponentiationNode(std::initializer_list<Scalar> const &arguments);

    std::string Type() const override;

    double Value() const override;
};
