
#include "expression_simplifier.hpp"

ExpressionSimplifier::ExpressionSimplifier(Scalar const &node, std::map<std::string, Scalar> const &node_map) : m_node(node), m_node_map(node_map)
{
}

Scalar ExpressionSimplifier::Simplify()
{
    Scalar distributed_ptr = ExpressionSimplifier(m_node, m_node_map).Distribute();
    Scalar combined_factors_ptr = ExpressionSimplifier(distributed_ptr, m_node_map).CombineFactors();
    Scalar combined_addends_ptr = ExpressionSimplifier(combined_factors_ptr, m_node_map).CombineAddends();
    Scalar factorized_ptr = ExpressionSimplifier(combined_addends_ptr, m_node_map).Factorize();

    return factorized_ptr;
}

Scalar ExpressionSimplifier::Identify()
{
    return Identify(m_node);
}

Scalar ExpressionSimplifier::Identify(Scalar const &node)
{

    for (auto &argument : node->Arguments())
    {
        argument = Identify(argument);
    }

    if (node->Type() == "PowerNode")
    {
        if (node->Argument(1)->Type() == "NumberNode")
        {
            if (Approximately(node->Argument(1)->Value(), 0.0))
            {
                return Scalar(new NumberNode(1.0));
            }
            else if (Approximately(node->Argument(1)->Value(), 1.0))
            {
                return node->Argument(0);
            }
            else if (node->Argument(0)->Type() == "NumberNode")
            {
                return Scalar(new NumberNode(std::pow(node->Argument(0)->Value(), node->Argument(1)->Value())));
            }
        }
    }
    else if (node->Type() == "MultiplicationNode")
    {
        if (node->Argument(0)->Type() == "NumberNode")
        {
            if (Approximately(node->Argument(0)->Value(), 0.0))
            {
                return Scalar(new NumberNode(0.0));
            }
            else if (Approximately(node->Argument(0)->Value(), 1.0))
            {
                return node->Argument(1);
            }
            else if (node->Argument(1)->Type() == "NumberNode")
            {
                return Scalar(new NumberNode(node->Argument(0)->Value() * node->Argument(1)->Value()));
            }
        }
        else if (node->Argument(1)->Type() == "NumberNode")
        {
            if (Approximately(node->Argument(1)->Value(), 0.0))
            {
                return Scalar(new NumberNode(0.0));
            }
            else if (Approximately(node->Argument(1)->Value(), 1.0))
            {
                return node->Argument(0);
            }
        }
    }
    else if (node->Type() == "DivisionNode")
    {
        if (node->Argument(0)->Type() == "NumberNode")
        {
            if (Approximately(node->Argument(0)->Value(), 0.0))
            {
                return Scalar(new NumberNode(0.0));
            }
            else if (node->Argument(1)->Type() == "NumberNode")
            {
                return Scalar(new NumberNode(node->Argument(0)->Value() / node->Argument(1)->Value()));
            }
        }
        else if (node->Argument(1)->Type() == "NumberNode")
        {
            if (Approximately(node->Argument(1)->Value(), 1.0))
            {
                return node->Argument(0);
            }
        }

        if (node->Argument(1)->Type() == "PowerNode")
        {
            if (node->Argument(1)->Argument(1)->Type() == "NumberNode")
            {
                return Scalar(new MultiplicationNode({node->Argument(0), Scalar(new PowerNode({node->Argument(1)->Argument(0), Scalar(new NumberNode(-1.0 * node->Argument(1)->Argument(1)->Value()))}))}));
            }
        }
    }
    else if (node->Type() == "AdditionNode")
    {
        if (node->Argument(0)->Type() == "NumberNode")
        {
            if (Approximately(node->Argument(0)->Value(), 0.0))
            {
                return node->Argument(1);
            }
            else if (node->Argument(1)->Type() == "NumberNode")
            {
                return Scalar(new NumberNode(node->Argument(0)->Value() + node->Argument(1)->Value()));
            }
        }
        else if (node->Argument(1)->Type() == "NumberNode")
        {
            if (Approximately(node->Argument(1)->Value(), 0.0))
            {
                return node->Argument(0);
            }
        }
    }
    else if (node->Type() == "SubtractionNode")
    {
        if (node->Argument(0)->Type() == "NumberNode")
        {
            if (Approximately(node->Argument(0)->Value(), 0.0))
            {
                return Scalar(new MultiplicationNode({Scalar(new NumberNode(-1.0)), node->Argument(1)}));
            }
            else if (node->Argument(1)->Type() == "NumberNode")
            {
                return Scalar(new NumberNode(node->Argument(0)->Value() - node->Argument(1)->Value()));
            }
        }
        else if (node->Argument(1)->Type() == "NumberNode")
        {
            if (Approximately(node->Argument(1)->Value(), 0.0))
            {
                return node->Argument(0);
            }
        }
        else
        {
            return Scalar(new AdditionNode({node->Argument(0), Scalar(new MultiplicationNode({Scalar(new NumberNode(-1.0)), node->Argument(1)}))}));
        }
    }
    else if (node->Type() == "SinNode")
    {
        if (node->Argument(0)->Type() == "NumberNode")
        {
            return Scalar(new NumberNode(std::sin(node->Argument(0)->Value())));
        }
    }
    else if (node->Type() == "CosNode")
    {
        if (node->Argument(0)->Type() == "NumberNode")
        {
            return Scalar(new NumberNode(std::cos(node->Argument(0)->Value())));
        }
    }
    else if (node->Type() == "TanNode")
    {
        if (node->Argument(0)->Type() == "NumberNode")
        {
            return Scalar(new NumberNode(std::tan(node->Argument(0)->Value())));
        }
    }
    else if (node->Type() == "AsinNode")
    {
        if (node->Argument(0)->Type() == "NumberNode")
        {
            return Scalar(new NumberNode(std::asin(node->Argument(0)->Value())));
        }
    }
    else if (node->Type() == "AcosNode")
    {
        if (node->Argument(0)->Type() == "NumberNode")
        {
            return Scalar(new NumberNode(std::acos(node->Argument(0)->Value())));
        }
    }
    else if (node->Type() == "AtanNode")
    {
        if (node->Argument(0)->Type() == "NumberNode")
        {
            return Scalar(new NumberNode(std::atan(node->Argument(0)->Value())));
        }
    }
    else if (node->Type() == "SqrtNode")
    {
        if (node->Argument(0)->Type() == "NumberNode")
        {
            return Scalar(new NumberNode(std::sqrt(node->Argument(0)->Value())));
        }
    }
    else if (node->Type() == "AbsNode")
    {
        if (node->Argument(0)->Type() == "NumberNode")
        {
            return Scalar(new NumberNode(std::abs(node->Argument(0)->Value())));
        }
    }
    else if (node->Type() == "ExpNode")
    {
        if (node->Argument(0)->Type() == "NumberNode")
        {
            return Scalar(new NumberNode(std::exp(node->Argument(0)->Value())));
        }
        else
        {
            std::vector<Scalar> factors = Factors(node->Argument(0));

            std::vector<Scalar> base_factors;
            std::vector<Scalar> exp_factors;

            std::partition_copy(std::cbegin(factors), std::cend(factors), std::back_inserter(base_factors), std::back_inserter(exp_factors), [](Scalar const &factor_ptr) -> bool
                                { return factor_ptr->Type() == "LnNode"; });

            if (base_factors.size() > 0)
            {
                Scalar base_ptr = std::reduce(std::next(std::cbegin(base_factors)), std::cend(base_factors), base_factors.front()->Argument(0),
                                              [](Scalar const &base_ptr, Scalar const &factor_ptr)
                                              {
                                                  return Scalar(new AdditionNode({base_ptr, factor_ptr->Argument(0)}));
                                              });

                if (exp_factors.size() > 0)
                {
                    Scalar exp_ptr = std::reduce(std::next(std::cbegin(exp_factors)), std::cend(exp_factors), exp_factors.front(),
                                                 [](Scalar const &exp_ptr, Scalar const &factor_ptr)
                                                 {
                                                     return Scalar(new MultiplicationNode({exp_ptr, factor_ptr}));
                                                 });

                    return Scalar(new PowerNode({base_ptr,
                                                 exp_ptr}));
                }

                return base_ptr;
            }
        }
    }
    else if (node->Type() == "LnNode")
    {
        if (node->Argument(0)->Type() == "NumberNode")
        {
            return Scalar(new NumberNode(std::log(node->Argument(0)->Value())));
        }
    }

    return node;

    throw std::invalid_argument("Scalar holds neither");
}

Scalar ExpressionSimplifier::Distribute()
{
    return Identify(Distribute(m_node));
}

Scalar ExpressionSimplifier::Distribute(Scalar const &node)
{
    for (auto &argument : node->Arguments())
    {
        argument = Distribute(argument);
    }

    std::vector<Scalar> factors = Factors(node);

    if (factors.size() > 0)
    {
        Scalar distributed_ptr = factors.front();

        for (Scalar const &factor : std::vector<Scalar>(std::next(std::cbegin(factors)), std::cend(factors)))
        {
            std::vector<Scalar> lhs_addends = Addends(distributed_ptr);
            std::vector<Scalar> rhs_addends = Addends(factor);

            for (auto lhs_addend_it = std::cbegin(lhs_addends); lhs_addend_it != std::cend(lhs_addends); ++lhs_addend_it)
            {
                for (auto rhs_addend_it = std::cbegin(rhs_addends); rhs_addend_it != std::cend(rhs_addends); ++rhs_addend_it)
                {
                    Scalar multiplication_ptr(new MultiplicationNode({*lhs_addend_it,
                                                                      *rhs_addend_it}));

                    if (lhs_addend_it == std::cbegin(lhs_addends) && rhs_addend_it == std::cbegin(rhs_addends))
                    {
                        distributed_ptr = multiplication_ptr;
                    }
                    else
                    {
                        distributed_ptr = Scalar(new AdditionNode({distributed_ptr, multiplication_ptr}));
                    }
                }
            }
        }

        return distributed_ptr;
    }

    return node;

    throw std::invalid_argument("Scalar holds neither");
}

Scalar ExpressionSimplifier::CombineFactors()
{
    return Identify(CombineFactors(m_node));
}

Scalar ExpressionSimplifier::CombineFactors(Scalar const &node)
{
    for (auto &argument : node->Arguments())
    {
        argument = CombineFactors(argument);
    }

    std::vector<Scalar> factors = Factors(node);

    if (factors.size() > 0)
    {
        std::vector<Scalar> constants;
        std::vector<Scalar> variables;

        // Separate the factors into their constants and their variables
        std::partition_copy(std::cbegin(factors), std::cend(factors), std::back_inserter(constants), std::back_inserter(variables), [](Scalar const &factor_ptr) -> bool
                            { return factor_ptr->Type() == "NumberNode"; });

        if (!variables.empty())
        {
            // Assess factors with O(n*(n-1)/2) complexity
            for (auto lhs_variable_it = std::begin(variables); lhs_variable_it != std::end(variables); ++lhs_variable_it)
            {
                for (auto rhs_variable_it = std::next(lhs_variable_it); rhs_variable_it != std::end(variables); ++rhs_variable_it)
                {
                    Scalar lhs_variable;
                    Scalar rhs_variable;

                    // Extract the variable of interest;
                    // if the node is of type "PowerNode" we want Argument(0)
                    if ((*lhs_variable_it)->Type() == "PowerNode")
                    {
                        lhs_variable = (*lhs_variable_it)->Argument(0);
                    }
                    else
                    {
                        lhs_variable = (*lhs_variable_it);
                    }

                    if ((*rhs_variable_it)->Type() == "PowerNode")
                    {
                        rhs_variable = (*rhs_variable_it)->Argument(0);
                    }
                    else
                    {
                        rhs_variable = (*rhs_variable_it);
                    }

                    // If the variables are equivalent sum their degrees
                    if (Node::Equivalent(lhs_variable, rhs_variable))
                    {
                        Scalar lhs_degree;
                        Scalar rhs_degree;

                        // If the variable is of type "PowerNode" then our degree is Argument(1)
                        // otherwise we have an implied degree of 1
                        if ((*lhs_variable_it)->Type() == "PowerNode")
                        {
                            lhs_degree = (*lhs_variable_it)->Argument(1);
                        }
                        else
                        {
                            lhs_degree = Scalar(new NumberNode(1.0));
                        }

                        if ((*rhs_variable_it)->Type() == "PowerNode")
                        {
                            rhs_degree = (*rhs_variable_it)->Argument(1);
                        }
                        else
                        {
                            rhs_degree = Scalar(new NumberNode(1.0));
                        }

                        // Add their degrees and exponentiate
                        *lhs_variable_it = Scalar(new PowerNode({lhs_variable, Scalar(new AdditionNode({lhs_degree, rhs_degree}))}));

                        // Remove the old variable
                        rhs_variable_it = variables.erase(rhs_variable_it);

                        if (rhs_variable_it == std::end(variables))
                        {
                            break;
                        }
                    }
                }
            }

            // Reduce the factors to a single combined node via repeated MultiplicationNode nodes
            Scalar combined_factors = std::reduce(std::next(std::cbegin(variables)), std::cend(variables), variables.front(),
                                                  [](Scalar const &combined_factors, Scalar const &combined_factor)
                                                  {
                                                      return Scalar(new MultiplicationNode({combined_factors, combined_factor}));
                                                  });

            // Reduce the constants to a single value via repeated multiplication
            if (!constants.empty())
            {
                double coefficient = std::transform_reduce(
                    std::cbegin(constants), std::cend(constants), 1.0,
                    [](double const &product_coefficient, double const &coefficient) -> double
                    {
                        return product_coefficient * coefficient;
                    },
                    [](Scalar const &coefficient) -> double
                    {
                        return coefficient->Value();
                    });

                return Scalar(new MultiplicationNode({Scalar(new NumberNode(coefficient)), combined_factors}));
            }
            else
            {
                return combined_factors;
            }
        }
    }

    return node;

    throw std::invalid_argument("Scalar holds neither");
}

Scalar ExpressionSimplifier::CombineAddends()
{
    return Identify(CombineAddends(m_node));
}

Scalar ExpressionSimplifier::CombineAddends(Scalar const &node)
{
    for (auto &argument : node->Arguments())
    {
        argument = CombineAddends(argument);
    }

    std::vector<Scalar> addends = Addends(node);

    if (addends.size() > 0)
    {
        // Assess addends with O(n*(n-1)/2) complexity
        for (auto addend_lhs_it = std::begin(addends); addend_lhs_it != std::end(addends); ++addend_lhs_it)
        {
            for (auto addend_rhs_it = std::next(addend_lhs_it); addend_rhs_it != std::end(addends); ++addend_rhs_it)
            {
                // Extract the factors from the lhs addend and the rhs addend
                auto lhs_factors = Factors(*addend_lhs_it);
                auto rhs_factors = Factors(*addend_rhs_it);

                // Separate the factors into their constants and their variables
                std::vector<Scalar> lhs_constants;
                std::vector<Scalar> rhs_constants;

                std::vector<Scalar> lhs_variables;
                std::vector<Scalar> rhs_variables;

                std::partition_copy(std::cbegin(lhs_factors), std::cend(lhs_factors), std::back_inserter(lhs_constants), std::back_inserter(lhs_variables), [](Scalar const &factor_ptr) -> bool
                                    { return factor_ptr->Type() == "NumberNode"; });
                std::partition_copy(std::cbegin(rhs_factors), std::cend(rhs_factors), std::back_inserter(rhs_constants), std::back_inserter(rhs_variables), [](Scalar const &factor_ptr) -> bool
                                    { return factor_ptr->Type() == "NumberNode"; });

                if (lhs_variables.size() > 0 && lhs_variables.size() == rhs_variables.size())
                {
                    // Check if all of the variables are equivalent, std::equal will not work for this
                    auto compare_variables = [](std::vector<Scalar> lhs_variables, std::vector<Scalar> rhs_variables) -> bool
                    {
                        for (auto lhs_variable : lhs_variables)
                        {
                            auto rhs_variable_it = std::find_if(std::cbegin(rhs_variables), std::cend(rhs_variables),
                                                                [&lhs_variable](Scalar const &rhs_variable) -> bool
                                                                {
                                                                    return Node::Equivalent(lhs_variable, rhs_variable);
                                                                });

                            if (rhs_variable_it == std::cend(rhs_variables))
                            {
                                return false;
                            }

                            rhs_variables.erase(rhs_variable_it);
                        }

                        return true;
                    };

                    if (compare_variables(lhs_variables, rhs_variables))
                    {
                        // If there are multiple constants per term, multiply them together and increment the coefficient
                        double coefficient;

                        if (lhs_constants.empty())
                        {
                            coefficient += 1.0;
                        }
                        else
                        {
                            coefficient += std::transform_reduce(
                                std::cbegin(lhs_constants), std::cend(lhs_constants), 1.0,
                                [](double const &product_coefficient, double const &coefficient) -> double
                                {
                                    return product_coefficient * coefficient;
                                },
                                [](Scalar const &lhs_coefficient) -> double
                                {
                                    return lhs_coefficient->Value();
                                });
                        }

                        if (rhs_constants.empty())
                        {
                            coefficient += 1.0;
                        }
                        else
                        {
                            coefficient += std::transform_reduce(
                                std::cbegin(rhs_constants), std::cend(rhs_constants), 1.0,
                                [](double const &product_coefficient, double const &coefficient) -> double
                                {
                                    return product_coefficient * coefficient;
                                },
                                [](Scalar const &rhs_coefficient) -> double
                                {
                                    return rhs_coefficient->Value();
                                });
                        }

                        // Recombining the variables via repeated MultiplicationNode
                        Scalar combined_variables = std::reduce(std::next(std::cbegin(lhs_variables)), std::cend(lhs_variables), lhs_variables.front(),
                                                                [](Scalar const &combined_variables, Scalar const &combined_variable) -> Scalar
                                                                {
                                                                    return Scalar(new MultiplicationNode({combined_variables, combined_variable}));
                                                                });

                        // Multiply by the coefficient
                        *addend_lhs_it = Scalar(new MultiplicationNode({std::shared_ptr<NumberNode>(new NumberNode(coefficient)), combined_variables}));

                        // Remove the old term
                        addend_rhs_it = addends.erase(addend_rhs_it);

                        // Make sure we don't segfault by attempting to access out-of-bounds memory!
                        if (addend_rhs_it == std::end(addends))
                        {
                            break;
                        }
                    }
                }
                else if (lhs_constants.size() > 0 && rhs_constants.size() > 0 && lhs_variables.size() == 0 && rhs_variables.size() == 0)
                {
                    // Sum the constants
                    double combined_constants;

                    for (auto lhs_constant : lhs_constants)
                    {
                        combined_constants += lhs_constant->Value();
                    }

                    for (auto rhs_constant : rhs_constants)
                    {
                        combined_constants += rhs_constant->Value();
                    }

                    *addend_lhs_it = Scalar(new NumberNode(combined_constants));

                    // Remove the old term
                    addend_rhs_it = addends.erase(addend_rhs_it);

                    // Make sure we don't segfault by attempting to access out-of-bounds memory!
                    if (addend_rhs_it == std::end(addends))
                    {
                        break;
                    }
                }
            }
        }

        // Sum the addends for the final result
        Scalar combined_addends = std::reduce(std::next(std::cbegin(addends)), std::cend(addends), addends.front(),
                                              [](Scalar const &combined_addends, Scalar const &combined_addend)
                                              {
                                                  return Scalar(new AdditionNode({combined_addends, combined_addend}));
                                              });

        return combined_addends;
    }

    return node;

    throw std::invalid_argument("Scalar holds neither");
}

Scalar ExpressionSimplifier::Factorize()
{
    return Identify(Factorize(m_node));
}

Scalar ExpressionSimplifier::Factorize(Scalar const &node)
{
    for (auto &argument : node->Arguments())
    {
        argument = Factorize(argument);
    }

    // [ 2*w*x, 2*w*y, 2*w*z ]
    std::vector<Scalar> addends = Addends(node);

    // [ [ 2, w, x ], [ 2, w, y ], [ 2, w, z ] ]
    std::vector<std::vector<Scalar>> factors_of_addends;

    std::transform(std::cbegin(addends), std::cend(addends), std::back_inserter(factors_of_addends),
                   [](Scalar const &addend_ptr) -> std::vector<Scalar>
                   {
                       return Factors(addend_ptr);
                   });

    if (factors_of_addends.size() > 1)
    {
        // [ 2, w, x ] ∩ [ 2, w, y ] ∩ [ 2, w, z ] = [ 2, w ]
        std::vector<Scalar> common_factors = std::reduce(std::next(std::cbegin(factors_of_addends)), std::cend(factors_of_addends), factors_of_addends.front(),
                                                         [](std::vector<Scalar> const &common_factors, std::vector<Scalar> const &factors) -> std::vector<Scalar>
                                                         {
                                                             std::vector<Scalar> factors_intersection;

                                                             std::set_intersection(std::cbegin(factors), std::cend(factors), std::cbegin(common_factors), std::cend(common_factors), std::back_inserter(factors_intersection),
                                                                                   [](Scalar const &lhs_ptr, Scalar const &rhs_ptr) -> bool
                                                                                   {
                                                                                       return !Node::Equivalent(lhs_ptr, rhs_ptr);
                                                                                   });

                                                             return factors_intersection;
                                                         });

        if (common_factors.size() > 0)
        {
            // [ 2, w, x ] - [ 2, w ] = [ x ] ...
            // [ 2, w, y ] - [ 2, w ] = [ x, y ] ...
            // [ 2, w, z ] - [ 2, w ] = [ x, y, z ]
            std::vector<Scalar> uncommon_factors = std::reduce(std::cbegin(factors_of_addends), std::cend(factors_of_addends), std::vector<Scalar>(),
                                                               [&common_factors](std::vector<Scalar> const &uncommon_factors, std::vector<Scalar> const &factors) -> std::vector<Scalar>
                                                               {
                                                                   std::vector<Scalar> factors_difference;

                                                                   std::set_difference(std::cbegin(factors), std::cend(factors), std::cbegin(common_factors), std::cend(common_factors), std::back_inserter(factors_difference),
                                                                                       [](Scalar const &lhs_ptr, Scalar const &rhs_ptr) -> bool
                                                                                       {
                                                                                           return !Node::Equivalent(lhs_ptr, rhs_ptr);
                                                                                       });

                                                                   std::copy(std::cbegin(uncommon_factors), std::cend(uncommon_factors), std::back_inserter(factors_difference));

                                                                   return factors_difference;
                                                               });

            if (uncommon_factors.size() > 0)
            {
                // [ 2, w ] = 2*w
                Scalar common_factors_ptr = std::reduce(std::next(std::cbegin(common_factors)), std::cend(common_factors), common_factors.front(),
                                                        [](Scalar const &common_factors_ptr, Scalar const &common_factor) -> Scalar
                                                        {
                                                            return Scalar(new MultiplicationNode({common_factors_ptr, common_factor}));
                                                        });

                // [ x, y, z ] = x+y+z
                Scalar uncommon_factors_ptr = std::reduce(std::next(std::cbegin(uncommon_factors)), std::cend(uncommon_factors), uncommon_factors.front(),
                                                          [](Scalar const &uncommon_factors_ptr, Scalar const &uncommon_factor) -> Scalar
                                                          {
                                                              return Scalar(new AdditionNode({uncommon_factors_ptr, uncommon_factor}));
                                                          });

                return Scalar(new MultiplicationNode({common_factors_ptr,
                                                      uncommon_factors_ptr}));
            }
        }
    }

    return node;

    throw std::invalid_argument("Scalar holds neither");
}

std::vector<Scalar> ExpressionSimplifier::Factors(Scalar const &node_node)
{
    std::vector<Scalar> factors;

    Factors(factors, node_node);

    return factors;
}

void ExpressionSimplifier::Factors(std::vector<Scalar> &factors, Scalar const &node_node)
{
    if (node_node->Type() == "MultiplicationNode")
    {
        Factors(factors, node_node->Argument(0));
        Factors(factors, node_node->Argument(1));
    }
    else
    {
        factors.emplace_back(node_node);
    }
}

std::vector<Scalar> ExpressionSimplifier::Addends(Scalar const &node_node)
{
    std::vector<Scalar> addends;

    Addends(addends, node_node);

    return addends;
}

void ExpressionSimplifier::Addends(std::vector<Scalar> &addends, Scalar const &node_node)
{
    if (node_node->Type() == "AdditionNode")
    {
        Addends(addends, node_node->Argument(0));
        Addends(addends, node_node->Argument(1));
    }
    else
    {
        addends.emplace_back(node_node);
    }
}