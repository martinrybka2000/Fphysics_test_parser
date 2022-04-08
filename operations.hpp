
#pragma once

#include <memory>
#include <cmath>
#include <iostream>

#include "node.hpp"

class AdditionNode : public Node
{
public:
    AdditionNode(std::initializer_list<Scalar> const &arguments);
    virtual ~AdditionNode() {}

    std::string Type() const override;
    std::string Print() const override;

    double Value() const override;
};

class SubtractionNode : public Node
{
public:
    SubtractionNode(std::initializer_list<Scalar> const &arguments);
    virtual ~SubtractionNode() {}

    std::string Type() const override;
    std::string Print() const override;

    double Value() const override;
};

class MultiplicationNode : public Node
{
public:
    MultiplicationNode(std::initializer_list<Scalar> const &arguments);
    virtual ~MultiplicationNode() {}

    std::string Type() const override;
    std::string Print() const override;

    double Value() const override;
};

class DivisionNode : public Node
{
public:
    DivisionNode(std::initializer_list<Scalar> const &arguments);
    virtual ~DivisionNode() {}

    std::string Type() const override;
    std::string Print() const override;

    double Value() const override;
};

class ExponentiationNode : public Node
{
public:
    ExponentiationNode(std::initializer_list<Scalar> const &arguments);
    virtual ~ExponentiationNode() {}

    std::string Type() const override;
    std::string Print() const override;

    double Value() const override;
};
