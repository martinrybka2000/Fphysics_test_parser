#pragma once

#include "node.hpp"

class ExpressionVisualizer
{
    Scalar m_node;
    std::map<std::string, Scalar> m_node_map;

public:
    // ExpressionVisualizer(Scalar const &node);
    ExpressionVisualizer(Scalar const &node, std::map<std::string, Scalar> const &node_map = {});

    std::string Visualize() const;

    void Visualize(std::ostream &ostream) const;

private:
    // void Visualize(std::ostream &ostream, Scalar const &node, size_t const &depth) const;
    void Visualize(std::ostream &ostream, Scalar const &node, size_t const &depth) const;

public:
    friend std::ostream &operator<<(std::ostream &ostream, ExpressionVisualizer const &expression_visualizer);
};