#include <iostream>

#include "node.hpp"
#include "operations.hpp"
#include "functions.hpp"

int main(int, char**) {
    std::cout << "Hello, world!\n";

    std::vector<Scalar> values;

    values.push_back(std::make_shared<VariableNode>("x", 2.13 / 2.0));
    values.push_back(std::make_shared<NumberNode>(2.34));

    std::shared_ptr<NumberNode> number(new NumberNode(4));
    *number = 6;

    std::shared_ptr<Node> adddd(new AdditionNode({values[1], number}));
    std::shared_ptr<Node> sinnnn(new SinNode({adddd}));
    std::shared_ptr<Node> divvvv(new DivisionNode({values[0], values[1]}));
    std::shared_ptr<Node> powwww(new PowerNode({sinnnn, divvvv}));

    std::shared_ptr<Node> tannnn(new TanNode({values[0]}));
    std::shared_ptr<Node> multtttt(new MultiplicationNode({tannnn, values[1]}));
    std::shared_ptr<Node> sqqqqqqrt(new SqrtNode({multtttt}));
    std::shared_ptr<Node> subbb(new SubtractionNode({powwww, sqqqqqqrt}));

    std::cout << "poww = " << subbb->Value() << "\n";

    std::cout << "expression = " << subbb->Print() << "\n";
    std::cout << "LaTex = " << subbb->PrintLaTex() << "\n";
}
