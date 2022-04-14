#pragma once

#include "node.hpp"

class ExpressionVisualizer
{
    Scalar m_node;

public:
    ExpressionVisualizer(Scalar const &node);

    std::string Visualize() const;

    void Visualize(std::ostream &ostream) const;

private:
    void Visualize(std::ostream &ostream, Scalar const &node, size_t const &depth) const;

public:
    friend std::ostream &operator<<(std::ostream &ostream, ExpressionVisualizer const &expression_visualizer);
};