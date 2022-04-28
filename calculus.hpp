/*
 * Copyright 2020 Casey Sanchez
 */

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
#include "expression_visualizer.hpp"

class Calculus
{
    Scalar m_node_variant;
    std::map<std::string, Scalar> m_node_map;

public:
    Calculus(Scalar const &node_variant, std::map<std::string, Scalar> const &node_map);

    Scalar Partial(Scalar const &with_respect_to_ptr);
    // Matrix Gradient(Scalar const &with_respect_to_11_ptr, Scalar const &with_respect_to_21_ptr, Scalar const &with_respect_to_31_ptr);
    // Scalar Divergence(Scalar const &with_respect_to_11_ptr, Scalar const &with_respect_to_21_ptr, Scalar const &with_respect_to_31_ptr);
    // Matrix Curl(Scalar const &with_respect_to_11_ptr, Scalar const &with_respect_to_21_ptr, Scalar const &with_respect_to_31_ptr);

private:
    Scalar Partial(Scalar const &node_variant, Scalar const &with_respect_to_ptr);
    // Matrix Gradient(Scalar const &node_variant, Scalar const &with_respect_to_11_ptr, Scalar const &with_respect_to_21_ptr, Scalar const &with_respect_to_31_ptr);
    // Scalar Divergence(Scalar const &node_variant, Scalar const &with_respect_to_11_ptr, Scalar const &with_respect_to_21_ptr, Scalar const &with_respect_to_31_ptr);
    // Matrix Curl(Scalar const &node_variant, Scalar const &with_respect_to_11_ptr, Scalar const &with_respect_to_21_ptr, Scalar const &with_respect_to_31_ptr);
};
