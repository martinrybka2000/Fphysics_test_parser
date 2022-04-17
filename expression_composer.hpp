
#pragma once

#include <memory>
#include <string>
#include <map>
#include <algorithm>

#include "node.hpp"
#include "operations.hpp"
#include "functions.hpp"

class ExpressionComposer
{
    Scalar m_node;

    std::map<std::string, Scalar> m_node_map;

public:
    ExpressionComposer(Scalar const &node, std::map<std::string, Scalar> const &node_map = {});

    std::string Compose() const;

    void Compose(std::ostream &ostream) const;

private:
    void Compose(std::ostream &ostream, Scalar const &node, uint32_t const &precedence = ~0) const;

public:
    friend std::ostream &operator<<(std::ostream &ostream, ExpressionComposer const &expression_composer);
};