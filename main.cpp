#include <iostream>

#include "node.hpp"
#include "operations.hpp"
#include "functions.hpp"

int main(int, char**) {
    std::cout << "Hello, world!\n";

    std::vector<Scalar> values;

    values.push_back(std::make_shared<VariableNode>(2.13 / 2.0));
    values.push_back(std::make_shared<VariableNode>(1));

    std::shared_ptr<AdditionNode> adddd(new AdditionNode({values[1], values[0]}));
    std::shared_ptr<SinNode> sinnnn(new SinNode({adddd}));
    std::shared_ptr<DivisionNode> divvvv(new DivisionNode({values[0], values[1]}));
    std::shared_ptr<PowerNode> powwww(new PowerNode({sinnnn, divvvv}));

    std::shared_ptr<TanNode> tannnn(new TanNode({values[0]}));
    std::shared_ptr<MultiplicationNode> multtttt(new MultiplicationNode({tannnn, values[1]}));
    std::shared_ptr<SqrtNode> sqqqqqqrt(new SqrtNode({multtttt}));
    std::shared_ptr<SubtractionNode> subbb(new SubtractionNode({powwww, sqqqqqqrt}));

    std::cout << "poww = " << subbb->Value() << "\n";

    std::cout << "expression = " << subbb->Print() << "\n";
    std::cout << "LaTex = " << subbb->PrintLaTex() << "\n";
}
