
#pragma once

#include <memory>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

#include "node.hpp"

#include "operations.hpp"
#include "functions.hpp"
#include "utils.hpp"

class ExpressionSimplifier
{
    Scalar m_node;
    std::map<std::string, Scalar> m_node_map;

public:
    ExpressionSimplifier(Scalar const &node, std::map<std::string, Scalar> const &node_map = {});

    Scalar Simplify();
    Scalar Identify();
    Scalar Distribute();
    Scalar CombineFactors();
    Scalar CombineAddends();
    Scalar Factorize();

private:
    Scalar Identify(Scalar const &node);
    Scalar Distribute(Scalar const &node);
    Scalar CombineFactors(Scalar const &node);
    Scalar CombineAddends(Scalar const &node);
    Scalar Factorize(Scalar const &node);

    static std::vector<Scalar> Factors(Scalar const &node_scalar);
    static std::vector<Scalar> Addends(Scalar const &node_scalar);

    static void Factors(std::vector<Scalar> &factors, Scalar const &node_scalar);
    static void Addends(std::vector<Scalar> &addends, Scalar const &node_scalar);
};