
#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

class Node;

using Scalar = std::shared_ptr<Node>;
class Node
{
protected:
    double m_value;
    std::vector<Scalar> m_arguments;

public:
    Node(double const &value = 0.0);
    Node(std::initializer_list<Scalar> const &arguments);
    virtual ~Node() {}

    Scalar &Argument(size_t const &index);
    Scalar Argument(size_t const &index) const;
    std::vector<Scalar> &Arguments();
    std::vector<Scalar> Arguments() const;

    virtual std::string Type() const;

    virtual double Value() const;

public:
    // static bool Equivalent(Scalar const &lhs_ptr, Scalar const &rhs_ptr);

    friend std::ostream &operator<<(std::ostream &ostream, Node const &node);
    friend std::ostream &operator<<(std::ostream &ostream, Scalar const &scalar);
};

class VariableNode : public Node
{
public:
    VariableNode(double const &value = 0.0);
    virtual ~VariableNode() {}

    std::string Type() const override;

    Node &operator=(double const &value);
};

class ConstantNode : public Node
{
public:
    ConstantNode(double const &value);
    virtual ~ConstantNode() {}

    std::string Type() const override;

    Node &operator=(Node const &node) = delete;
};
