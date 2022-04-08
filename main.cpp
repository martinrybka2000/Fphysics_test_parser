#include <iostream>

#include "node.hpp"
#include "operations.hpp"
#include "functions.hpp"

int main(int, char**) {
    std::cout << "Hello, world!\n";

    std::vector<Scalar> values;

    values.push_back(std::make_shared<VariableNode>(2.13 / 2.0));
    values.push_back(std::make_shared<Node>());
    values.push_back(std::make_shared<VariableNode>(1));
    std::shared_ptr<AdditionNode> adddd(new AdditionNode({values[2], values[0]}));
    std::shared_ptr<SinNode> sinnnn(new SinNode({adddd}));
    std::shared_ptr<DivisionNode> divvvv(new DivisionNode({values[0], values[2]}));
    std::shared_ptr<ExponentiationNode> powwww(new ExponentiationNode({sinnnn, divvvv}));

    for (auto val : values)
    {
        std::cout << "Type: " << val->Type() << "Value: " << val->Value() << std::endl;
    }

    std::cout << " = " << adddd->Value() << "\n";
    std::cout << "poww = " << powwww->Value() << "\n";

    std::cout << "expression = " << powwww->Print() << "\n";
}
