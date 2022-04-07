#include <iostream>

#include "node.hpp"
// #include "operations.hpp"
// #include "functions.hpp"

int main(int, char**) {
    std::cout << "Hello, world!\n";
    std::cout << "Test 2\n";

    std::shared_ptr<ConstantNode> pi(new ConstantNode(3.14159265358979323846));
    std::shared_ptr<ConstantNode> e(new ConstantNode(2.71828182845904523536));

    std::cout << pi->Type() << pi->Value();
}
