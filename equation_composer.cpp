
#include "equation_composer.hpp"

EquationComposer::EquationComposer(Equation const &equation, std::map<std::string, Scalar> const &node_map) : m_equation(equation), m_node_map(node_map)
{
}

std::string EquationComposer::Compose() const
{
    std::ostringstream ostringstream;

    Compose(ostringstream);

    return ostringstream.str();
}

void EquationComposer::Compose(std::ostream &ostream) const
{
    ostream << ExpressionComposer(m_equation.m_lhs, m_node_map) << " = " << ExpressionComposer(m_equation.m_rhs, m_node_map);
}

std::ostream &
operator<<(std::ostream &ostream, EquationComposer const &equation_composer)
{
    equation_composer.Compose(ostream);

    return ostream;
}