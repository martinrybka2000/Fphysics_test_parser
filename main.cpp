#include <iostream>

#include "node.hpp"
#include "operations.hpp"
#include "functions.hpp"
#include "expression_visualizer.hpp"
#include "expression_parser.hpp"
#include "expression_composer.hpp"
#include "utils.hpp"
#include "expression_simplifier.hpp"
#include "equation_parser.hpp"

// !ToDo add comments, add expresion_composer insted of printLatex()

int main(int, char **)
{
    std::shared_ptr<VariableNode> x(new VariableNode(3.0));
    std::shared_ptr<VariableNode> y(new VariableNode(2.0));
    std::shared_ptr<VariableNode> z(new VariableNode(0.1));

    std::map<std::string, std::shared_ptr<Node>> node_map = {{"x", x}, {"y", y}};
    node_map.emplace("z", z);

    ExpressionParser expression_parser("\\frac{y}{x}*x^{x+2}*x^{x+2}*x^{x+2}*sin(5 + y*x)*cos(2*y^2) + z", node_map);
    // ExpressionParser expression_parser("\\frac{\\sin\\left(5*x+4\\right)}{\\frac{x}{y^{4}}}*\\cos\\left(2*x+y^{2*x}\\right)", node_map);
    // ExpressionParser expression_parser("\\frac{x}{y^{x+2.5/1}} * sin\\left(cos\\left(exp\\left(x^3+2* y + 4 + y + x^3 + 2.6\\right)\\right)\\right)+1 + 5*7", node_map);

    std::shared_ptr<Node> node_ptr = expression_parser.Parse();

    std::cout << "Visualized expression tree: " << std::endl;
    std::cout << ExpressionVisualizer(node_ptr, node_map) << std::endl
              << std::endl;

    ExpressionComposer espresion_composer(node_ptr, node_map);
    std::cout << "Latex output composed = " << espresion_composer << std::endl;

    ExpressionSimplifier expresion_simplifier(node_ptr, node_map);
    expresion_simplifier.Simplify();

    std::cout << "After simplify ______________________________________" << std::endl
              << "Visualized expression tree: " << std::endl;
    std::cout << ExpressionVisualizer(node_ptr, node_map) << std::endl
              << std::endl;

    ExpressionComposer espresion_composer2(node_ptr, node_map);
    std::cout << "Latex output composed = " << espresion_composer2 << std::endl;

    EquationParser equation_parser("2*x = x+x+y", node_map);
    Equation eq = equation_parser.GetEquation();

    std::cout << "Is equation equal: " << equation_parser.Equal() << std::endl
              << "equation :" << std::endl
              << ExpressionComposer(eq.m_lhs, node_map) << " = " << ExpressionComposer(eq.m_rhs, node_map) << std::endl;
}
