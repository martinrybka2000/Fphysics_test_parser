
#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

class Node;

using Scalar = std::shared_ptr<Node>;

/*****************************************
 * Node ->
 * * Main Node class for equation binary tree
 * ! Not a pure virtual class
 * @param m_value storing the numerical value of the Node
 * @param m_argments pointers to the children nodes
 ******************************************/
class Node
{
protected:
    double m_value;
    std::vector<Scalar> m_arguments;

public:
    Node(double const &value = 0.0);
    Node(std::initializer_list<Scalar> const &arguments);
    virtual ~Node() {}

    // getters and setters fot the m_arguments
    Scalar &Argument(size_t const &index);
    Scalar Argument(size_t const &index) const;
    std::vector<Scalar> &Arguments();
    std::vector<Scalar> Arguments() const;

    virtual std::string Type() const;

    virtual double Value() const;
    virtual std::string Print() const;

public:
    // static bool Equivalent(Scalar const &lhs_ptr, Scalar const &rhs_ptr);
    static std::string Out(std::string &str);

    friend std::ostream &operator<<(std::ostream &ostream, Node const &node);
    friend std::ostream &operator<<(std::ostream &ostream, Scalar const &scalar);
};

/*****************************************
 * VariableNode ->
 * * Derived class for variables
 * ! Used for variables lke 'x' 'v' 'a' etc
 * @param m_variable string for storing name of the variable
 ******************************************/
class VariableNode : public Node
{
    // const std::string m_variable;

public:
    VariableNode(double const &value = 0.0);
    virtual ~VariableNode() {}

    std::string Type() const override;
    std::string Print() const override;

    Node &operator=(double const &value);
};

/*****************************************
 * NumberNode ->
 * * Derived class for numercial variables
 * @param
 ******************************************/
class NumberNode : public Node
{
public:
    NumberNode(double const &value);
    virtual ~NumberNode() {}

    std::string Type() const override;
    std::string Print() const override;

    Node &operator=(Node const &node) = delete;
};
