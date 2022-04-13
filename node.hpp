
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

/*****************************************
 * Node ->
 * * Main Node class for equation binary tree
 * ! Not a pure virtual class
 * @param m_value storing the numerical value of the Node
 * @param m_argments pointers to the children nodes
 * Todo LateX string returning method
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
    virtual std::string PrintLaTex() const;

public:
    // static bool Equivalent(Scalar const &lhs_ptr, Scalar const &rhs_ptr);
    static std::string Out(std::string &str);

    friend std::ostream &operator<<(std::ostream &ostream, Node const &node);
    friend std::ostream &operator<<(std::ostream &ostream, Scalar const &scalar);
};

/*****************************************
 * VariableNode ->
 * * Derived class for variables
 * ToDo Add a string for storing variable name
 * @param
 ******************************************/
class VariableNode : public Node
{
public:
    VariableNode(double const &value = 0.0);
    virtual ~VariableNode() {}

    std::string Type() const override;
    std::string Print() const override;
    std::string PrintLaTex() const override;

    Node &operator=(double const &value);
};

/*****************************************
 * ConstantNode ->
 * * Derived class for constant variables
 * ? Dont know if gonna stay
 * @param
 ******************************************/
class ConstantNode : public Node
{
public:
    ConstantNode(double const &value);
    virtual ~ConstantNode() {}

    std::string Type() const override;

    Node &operator=(Node const &node) = delete;
};
