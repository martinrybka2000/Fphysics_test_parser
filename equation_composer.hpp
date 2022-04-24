#pragma once

#include "expression_composer.hpp"
#include "equation_parser.hpp"

class EquationComposer
{
private:
    Equation m_equation;

    std::map<std::string, Scalar> m_node_map;

public:
    EquationComposer(Equation const &equation, std::map<std::string, Scalar> const &node_map = {});

    std::string Compose() const;

    void Compose(std::ostream &ostream) const;

    friend std::ostream &operator<<(std::ostream &ostream, EquationComposer const &equation_composer);
};