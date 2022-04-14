
#include "expression_visualizer.hpp"

// ExpressionVisualizer::ExpressionVisualizer(Scalar const &node) : m_node(node)
// {
// }

ExpressionVisualizer::ExpressionVisualizer(Scalar const &node, std::map<std::string, Scalar> const &node_map) : m_node(node), m_node_map(node_map)
{
}

std::string ExpressionVisualizer::Visualize() const
{
    std::ostringstream ostringstream;

    Visualize(ostringstream);

    return ostringstream.str();
}

void ExpressionVisualizer::Visualize(std::ostream &ostream) const
{
    Visualize(ostream, m_node, 0);
}

// void ExpressionVisualizer::Visualize(std::ostream &ostream, Scalar const &node, size_t const &depth) const
// {
//     ostream << std::string(depth * 4, ' ');

//     ostream << "[" << node->Type() << "] ";

//     if (node->Type() == "VariableNode")
//     {
//         ostream << node->Print() << " = " << node << std::endl;
//     }
//     else
//     {
//         ostream << node << std::endl;
//     }

//     for (auto const &argument_ptr : node->Arguments())
//     {
//         Visualize(ostream, argument_ptr, depth + 1);
//     }
// }

void ExpressionVisualizer::Visualize(std::ostream &ostream, Scalar const &node, size_t const &depth) const
{
    ostream << std::string(depth * 4, ' ');

    ostream << "[" << node->Type() << "] ";

    auto node_it = std::find_if(std::cbegin(m_node_map), std::cend(m_node_map),
                                [&node](std::pair<std::string, Scalar> const &node_pair)
                                {
                                    return node_pair.second == node;
                                });

    if (node_it != std::cend(m_node_map))
    {
        ostream << node_it->first << " = " << node << std::endl;
    }
    else
    {
        ostream << node << std::endl;
    }

    for (auto const &argument_ptr : node->Arguments())
    {
        Visualize(ostream, argument_ptr, depth + 1);
    }
}

std::ostream &operator<<(std::ostream &ostream, ExpressionVisualizer const &expression_visualizer)
{
    expression_visualizer.Visualize(ostream);

    return ostream;
}
