#include <iostream>

#include "node.hpp"
#include "operations.hpp"
#include "functions.hpp"
#include "expression_visualizer.hpp"
#include "expression_parser.hpp"

int main(int, char **)
{

    std::vector<Scalar> values;

    values.push_back(std::make_shared<VariableNode>(2.13 / 2.0));
    values.push_back(std::make_shared<VariableNode>(2.34));

    std::shared_ptr<NumberNode> number(new NumberNode(4));

    std::shared_ptr<Node> adddd(new AdditionNode({values[1], number}));
    std::shared_ptr<Node> sinnnn(new SinNode({adddd}));
    std::shared_ptr<Node> divvvv(new DivisionNode({values[0], values[1]}));
    std::shared_ptr<Node> powwww(new PowerNode({sinnnn, divvvv}));

    std::shared_ptr<Node> tannnn(new TanNode({values[0]}));
    std::shared_ptr<Node> multtttt(new MultiplicationNode({tannnn, values[1]}));
    std::shared_ptr<Node> sqqqqqqrt(new SqrtNode({multtttt}));
    std::shared_ptr<Node> subbb(new SubtractionNode({powwww, sqqqqqqrt}));

    std::cout << "Visualized expression tree: " << std::endl;
    std::cout << ExpressionVisualizer(subbb) << std::endl
              << std::endl;

    std::cout << "poww = " << subbb->Value() << "\n";

    std::cout << "expression = " << subbb->Print() << "\n";
    std::cout << "LaTex = " << subbb->PrintLaTex() << "\n\n";

    std::shared_ptr<VariableNode> x(new VariableNode(3.0));
    std::shared_ptr<VariableNode> y(new VariableNode(2.0));

    std::map<std::string, std::shared_ptr<Node>> node_map = {{"x", x}, {"y", y}};

    ExpressionParser expression_parser("\\frac{y}{x}*x^{x+2.4}*x^{x+2}*x^{x+2}*sin(5 + y*x)", node_map);

    std::shared_ptr<Node> node_ptr = expression_parser.Parse();

    std::cout << "Visualized expression tree: " << std::endl;
    std::cout << ExpressionVisualizer(node_ptr, node_map) << std::endl
              << std::endl;

    std::cout << "Latex output = " << node_ptr->PrintLaTex() << std::endl;
}
