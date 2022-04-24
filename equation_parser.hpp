
#include "expression_parser.hpp"

struct Equation
{
    Equation(){};

    Equation(Scalar const lhs, Scalar const rhs)
    {
        m_lhs = lhs;
        m_rhs = rhs;
    };

    Scalar m_lhs;
    Scalar m_rhs;
};

class EquationParser
{
    Equation m_equation;

public:
    EquationParser(std::string const &equation_str, std::map<std::string, Scalar> const &node_map = {}, std::shared_ptr<ExpressionParserContext> const &parser_context = ExpressionParserContext::default_context);

    bool Equal() const;

    Equation GetEquation();
};
