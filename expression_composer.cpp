
#include "expression_composer.hpp"

ExpressionComposer::ExpressionComposer(Scalar const &node, std::map<std::string, Scalar> const &node_map) : m_node(node), m_node_map(node_map)
{
}

std::string ExpressionComposer::Compose() const
{
    std::ostringstream ostringstream;

    Compose(ostringstream);

    return ostringstream.str();
}

void ExpressionComposer::Compose(std::ostream &ostream) const
{
    Compose(ostream, m_node);
}

void ExpressionComposer::Compose(std::ostream &ostream, Scalar const &node, uint32_t const &precedence) const
{
    if (node->Type() == "VariableNode")
    {
        auto node_it = std::find_if(std::cbegin(m_node_map), std::cend(m_node_map),
                                    [&node](std::pair<std::string, Scalar> const &node_pair)
                                    {
                                        return node_pair.second == node;
                                    });

        if (node_it != std::cend(m_node_map))
        {
            ostream << node_it->first;
        }
        else
        {
            ostream << node;
        }
    }
    else if (node->Type() == "NumberNode")
    {
        auto node_it = std::find_if(std::cbegin(m_node_map), std::cend(m_node_map),
                                    [&node](std::pair<std::string, Scalar> const &node_pair)
                                    {
                                        return node_pair.second == node;
                                    });

        if (node_it != std::cend(m_node_map))
        {
            ostream << node_it->first;
        }
        else
        {
            ostream << node;
        }
    }
    else if (node->Type() == "PowerNode")
    {
        Compose(ostream, Scalar(node->Argument(0)), 0);

        ostream << "^{";

        Compose(ostream, Scalar(node->Argument(1)), 0);

        ostream << "}";
    }
    else if (node->Type() == "MultiplicationNode")
    {
        if (precedence < 1)
        {
            ostream << "\\left(";

            Compose(ostream, Scalar(node->Argument(0)), 1);

            ostream << "\\cdot ";

            Compose(ostream, Scalar(node->Argument(1)), 1);

            ostream << "\\right)";
        }
        else
        {
            Compose(ostream, Scalar(node->Argument(0)), 1);

            ostream << "\\cdot ";

            Compose(ostream, Scalar(node->Argument(1)), 1);
        }
    }
    else if (node->Type() == "DivisionNode")
    {
        if (precedence < 1)
        {
            ostream << "\\left(";

            ostream << "\\frac{";

            Compose(ostream, Scalar(node->Argument(0)), 1);

            ostream << "}{";

            Compose(ostream, Scalar(node->Argument(1)), 1);

            ostream << "}";

            ostream << "\\right)";
        }
        else
        {
            ostream << "\\frac{";

            Compose(ostream, Scalar(node->Argument(0)), 1);

            ostream << "}{";

            Compose(ostream, Scalar(node->Argument(1)), 1);

            ostream << "}";
        }
    }
    else if (node->Type() == "AdditionNode")
    {
        if (precedence < 2)
        {
            ostream << "\\left(";

            Compose(ostream, Scalar(node->Argument(0)), 2);

            ostream << "+";

            Compose(ostream, Scalar(node->Argument(1)), 2);

            ostream << "\\right)";
        }
        else
        {
            Compose(ostream, Scalar(node->Argument(0)), 2);

            ostream << "+";

            Compose(ostream, Scalar(node->Argument(1)), 2);
        }
    }
    else if (node->Type() == "SubtractionNode")
    {
        if (precedence < 2)
        {
            ostream << "\\left(";

            Compose(ostream, Scalar(node->Argument(0)), 2);

            ostream << "-";

            Compose(ostream, Scalar(node->Argument(1)), 2);

            ostream << "\\right)";
        }
        else
        {
            Compose(ostream, Scalar(node->Argument(0)), 2);

            ostream << "-";

            Compose(ostream, Scalar(node->Argument(1)), 2);
        }
    }
    else if (node->Type() == "SinNode")
    {
        ostream << "sin\\left(";

        Compose(ostream, Scalar(node->Argument(0)), ~0);

        ostream << "\\right)";
    }
    else if (node->Type() == "CosNode")
    {
        ostream << "cos\\left(";

        Compose(ostream, Scalar(node->Argument(0)), ~0);

        ostream << "\\right)";
    }
    else if (node->Type() == "TanNode")
    {
        ostream << "tan\\left(";

        Compose(ostream, Scalar(node->Argument(0)), ~0);

        ostream << "\\right)";
    }
    else if (node->Type() == "AsinNode")
    {
        ostream << "asin\\left(";

        Compose(ostream, Scalar(node->Argument(0)), ~0);

        ostream << "\\right)";
    }
    else if (node->Type() == "AcosNode")
    {
        ostream << "acos\\left(";

        Compose(ostream, Scalar(node->Argument(0)), ~0);

        ostream << "\\right)";
    }
    else if (node->Type() == "AtanNode")
    {
        ostream << "atan\\left(";

        Compose(ostream, Scalar(node->Argument(0)), ~0);

        ostream << "\\right)";
    }
    else if (node->Type() == "SqrtNode")
    {
        ostream << "sqrt\\left(";

        Compose(ostream, Scalar(node->Argument(0)), ~0);

        ostream << "\\right)";
    }
    else if (node->Type() == "AbsNode")
    {
        ostream << "abs\\left(";

        Compose(ostream, Scalar(node->Argument(0)), ~0);

        ostream << "\\right)";
    }
    else if (node->Type() == "ExpNode")
    {
        ostream << "exp\\left(";

        Compose(ostream, Scalar(node->Argument(0)), ~0);

        ostream << "\\right)";
    }
    else if (node->Type() == "LnNode")
    {
        ostream << "ln\\left(";

        Compose(ostream, Scalar(node->Argument(0)), ~0);

        ostream << "\\right)";
    }
    else if (node->Type() == "DeterminantNode")
    {
        ostream << "det\\left(";

        Compose(ostream, Scalar(node->Argument(0)), ~0);

        ostream << "\\right)";
    }
    else if (node->Type() == "InverseNode")
    {
        ostream << "inv\\left(";

        Compose(ostream, Scalar(node->Argument(0)), ~0);

        ostream << "\\right)";
    }
    else
    {
        throw std::invalid_argument("Node of unknown type: " + node->Type());
    }
}

std::ostream &operator<<(std::ostream &ostream, ExpressionComposer const &expression_composer)
{
    expression_composer.Compose(ostream);

    return ostream;
}