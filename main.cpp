#include <iostream>

#include "node.hpp"
#include "operations.hpp"
#include "functions.hpp"

int main(int, char**) {
    std::cout << "Hello, world!\n";

    std::vector<Scalar> values;

    values.push_back(std::make_shared<ConstantNode>(2.13 / 2.0));
    values.push_back(std::make_shared<Node>());
    values.push_back(std::make_shared<VariableNode>(1));
    std::shared_ptr<AdditionNode> adddd(new AdditionNode({values[2], values[0]}));
    std::shared_ptr<SinNode> sinnnn(new SinNode({adddd}));

    for (auto val : values)
    {
        std::cout << "Type: " << val->Type() << "Value: " << val->Value() << std::endl;
    }

    std::cout << " = " << adddd->Value() << "\n";
    std::cout << "sin = " << sinnnn->Value() << "\n";
}
