#include "node.hpp"

Node::Node(double const &value) : m_value(value)
{
}

Node::Node(std::initializer_list<Scalar> const &arguments) : m_arguments(arguments)
{
}

/*****************************************
 * Argument ->
 * * Returns a pointer to child Node by index
 * @param index index of the pointer to return
 ******************************************/
Scalar &Node::Argument(size_t const &index)
{
    return m_arguments.at(index);
}

Scalar Node::Argument(size_t const &index) const
{
    return m_arguments.at(index);
}

/*****************************************
 * Arguments ->
 * * Returns all children Nodes
 * @param
 ******************************************/
std::vector<Scalar> &Node::Arguments()
{
    return m_arguments;
}

std::vector<Scalar> Node::Arguments() const
{
    return m_arguments;
}

/*****************************************
 * Type ->
 * * Returns the type of the Node
 * @param
 ******************************************/
std::string Node::Type() const
{
    return "Node";
}

/*****************************************
 * VALUE ->
 * * Returns numerical value of the Node
 * @param m_value stored value [double]
 ******************************************/
double Node::Value() const
{
    return m_value;
}

// Dont know probably for checking if one tree == other tree
/*
bool Node::Equivalent(Scalar const &lhs_ptr, Scalar const &rhs_ptr)
{
    if (lhs_ptr->Type() == rhs_ptr->Type()) {
        std::vector<Scalar> lhs_args = lhs_ptr->Arguments();
        std::vector<Scalar> rhs_args = rhs_ptr->Arguments();

        if (lhs_args.size() == 0) {
            if (lhs_ptr->Type() == "VariableNode") {
                return lhs_ptr == rhs_ptr;
            }
            else if (lhs_ptr->Type() == "ConstantNode") {
                return Approximately(lhs_ptr->Value(), rhs_ptr->Value());
            }
        }
        else {
            for (auto lhs_arg : lhs_args) {
                if (std::find_if(std::cbegin(rhs_args), std::cend(rhs_args), [&lhs_arg](Scalar const &rhs_arg) -> bool { return Node::Equivalent(lhs_arg, rhs_arg); }) == std::cend(rhs_args)) {
                    return false;
                }
            }

            return true;
        }
    }

    return false;
}
*/

std::ostream &operator<<(std::ostream &ostream, Node const &node)
{
    /*   std::complex<double> complex = node.Value();

       if (!Approximately(complex.real(), 0.0) && !Approximately(complex.imag(), 0.0)) {
           ostream << complex.real() << (complex.imag() > 0.0 ? "+" : "") << complex.imag() << "i";
       }
       else if(!Approximately(complex.real(), 0.0)) {
           ostream << complex.real();
       }
       else if(!Approximately(complex.imag(), 0.0)) {
           ostream << complex.imag() << "i";
       }
       else {
           ostream << 0.0;
       }
       return ostream;
   */
    ostream << node.Value();
    return ostream;
}

std::ostream &operator<<(std::ostream &ostream, Scalar const &scalar)
{
    ostream << *scalar;

    return ostream;
}

VariableNode::VariableNode(double const &value) : Node(value)
{
}

std::string VariableNode::Type() const
{
    return "VariableNode";
}

Node &VariableNode::operator=(double const &value)
{
    m_value = value;

    return *this;
}

ConstantNode::ConstantNode(double const &value) : Node(value)
{
}

std::string ConstantNode::Type() const
{
    return "ConstantNode";
}
