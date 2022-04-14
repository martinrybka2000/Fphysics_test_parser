
#include "expression_parser.hpp"

std::shared_ptr<ExpressionParserContext> const ExpressionParserContext::default_context(new ExpressionParserContext());

ExpressionParserContext::ExpressionParserContext() : m_expression_id(0), m_function_id(0), m_constant_id(0), m_matrix_id(0)
{
}

std::string ExpressionParserContext::NextExpressionName()
{
    return "E_" + std::to_string(m_expression_id++);
}

std::string ExpressionParserContext::NextFunctionName()
{
    return "F_" + std::to_string(m_function_id++);
}

std::string ExpressionParserContext::NextConstantName()
{
    return "C_" + std::to_string(m_constant_id++);
}

std::string ExpressionParserContext::NextMatrixName()
{
    return "M_" + std::to_string(m_matrix_id++);
}

ExpressionParser::ExpressionParser(std::string const &expression_str, std::map<std::string, Scalar> const &node_map, std::shared_ptr<ExpressionParserContext> const &parser_context, bool const &clean_and_verify) : m_expression_str(expression_str), m_node_map(node_map), m_parser_context(parser_context)
{
    if (clean_and_verify)
    {
        Clean();

        Verify();
    }
}

ExpressionParser::ExpressionParser(std::string const &expression_str, std::map<std::string, Scalar> const &node_map, std::shared_ptr<ExpressionParserContext> const &parser_context) : ExpressionParser(expression_str, node_map, parser_context, true)
{
}

Scalar ExpressionParser::Parse()
{
    return Brackets(m_expression_str);
}

void ExpressionParser::Clean()
{
    m_expression_str.erase(std::remove_if(std::begin(m_expression_str), std::end(m_expression_str), ::isspace), std::end(m_expression_str));

    if (m_expression_str.empty())
    {
        throw std::invalid_argument("Expression is empty");
    }

    std::regex left_right_regex("\\\\left|\\\\right");

    m_expression_str = std::regex_replace(m_expression_str, left_right_regex, "");
}

void ExpressionParser::Verify()
{
    std::regex reserved_regex("^E_[0-9]+$|^F_[0-9]+$|^C_[0-9]+$|^M_[0-9]+$");

    std::smatch reserved_match;

    for (auto const &[node_name, node_ptr] : m_node_map)
    {
        if (std::regex_search(std::cbegin(node_name), std::cend(node_name), reserved_match, reserved_regex))
        {
            throw std::invalid_argument("Reserved node name: " + node_name);
        }
    }
}

Scalar ExpressionParser::Brackets(std::string const &expression_str)
{
    std::regex bracket_regex("^(.*)(\\(|\\[|\\{)(.*?)(\\)|\\]|\\})(.*)$");
    std::regex function_regex("^(.*(\\+|\\-|\\*|\\/|\\^|\\(|\\[|\\{))(.*)$|^(.*)$");

    std::smatch bracket_match;
    std::smatch function_match;

    if (std::regex_search(std::cbegin(expression_str), std::cend(expression_str), bracket_match, bracket_regex))
    {
        if ((bracket_match[2].str() == "(" && bracket_match[4].str() == ")") ||
            (bracket_match[2].str() == "[" && bracket_match[4].str() == "]") ||
            (bracket_match[2].str() == "{" && bracket_match[4].str() == "}"))
        {
            Scalar expression_variant = Functions(bracket_match[3].str());

            std::string expression_name = m_parser_context->NextExpressionName();

            m_node_map.emplace(expression_name, expression_variant);

            return Brackets(bracket_match[1].str() + expression_name + bracket_match[5].str());
        }
        else
        {
            throw std::invalid_argument("Bracket mismatch: " + bracket_match[2].str() + " and " + bracket_match[4].str());
        }
    }

    return Functions(expression_str);
}

Scalar ExpressionParser::Functions(std::string const &expression_str)
{
    std::regex function_regex("^(.*)(cos|sin|tan|acos|asin|atan|sqrt|abs|exp|ln|det|inv)(E_\\d+)(.*?)$|^(.*)(\\\\frac)(E_\\d+)(E_\\d+)(.*?)$");

    std::smatch function_match;

    if (std::regex_search(std::cbegin(expression_str), std::cend(expression_str), function_match, function_regex))
    {
        if (!function_match[2].str().empty())
        {
            Scalar arg_variant = m_node_map.at(function_match[3].str());

            Scalar function_variant;

            if (function_match[2].str() == "cos")
            {
                function_variant = std::shared_ptr<CosNode>(new CosNode({arg_variant}));
            }
            else if (function_match[2].str() == "sin")
            {
                function_variant = std::shared_ptr<SinNode>(new SinNode({arg_variant}));
            }
            else if (function_match[2].str() == "tan")
            {
                function_variant = std::shared_ptr<TanNode>(new TanNode({arg_variant}));
            }
            else if (function_match[2].str() == "acos")
            {
                function_variant = std::shared_ptr<AcosNode>(new AcosNode({arg_variant}));
            }
            else if (function_match[2].str() == "asin")
            {
                function_variant = std::shared_ptr<AsinNode>(new AsinNode({arg_variant}));
            }
            else if (function_match[2].str() == "atan")
            {
                function_variant = std::shared_ptr<AtanNode>(new AtanNode({arg_variant}));
            }
            else if (function_match[2].str() == "sqrt")
            {
                function_variant = std::shared_ptr<SqrtNode>(new SqrtNode({arg_variant}));
            }
            else if (function_match[2].str() == "abs")
            {
                function_variant = std::shared_ptr<AbsNode>(new AbsNode({arg_variant}));
            }
            else if (function_match[2].str() == "exp")
            {
                function_variant = std::shared_ptr<ExpNode>(new ExpNode({arg_variant}));
            }
            else if (function_match[2].str() == "ln")
            {
                function_variant = std::shared_ptr<LnNode>(new LnNode({arg_variant}));
            }
            else
            {
                throw std::invalid_argument("Unrecognized function: " + function_match[2].str());
            }

            std::string function_name = m_parser_context->NextFunctionName();

            m_node_map.emplace(function_name, function_variant);

            return Functions(function_match[1].str() + function_name + function_match[4].str());
        }
        else if (!function_match[6].str().empty())
        {
            Scalar lhs_arg_variant = m_node_map.at(function_match[7].str());
            Scalar rhs_arg_variant = m_node_map.at(function_match[8].str());

            Scalar function_variant;

            if (function_match[6].str() == "\\frac")
            {
                function_variant = Scalar(new DivisionNode({lhs_arg_variant, rhs_arg_variant}));
            }
            else
            {
                throw std::invalid_argument("Unrecognized function: " + function_match[6].str());
            }

            std::string function_name = m_parser_context->NextFunctionName();

            m_node_map.emplace(function_name, function_variant);

            return Functions(function_match[5].str() + function_name + function_match[9].str());
        }
    }

    return Operators(expression_str);
}

Scalar ExpressionParser::Operators(std::string const &expression_str)
{
    std::regex operator_regex("^(.*[^\\+\\-\\*\\/\\^])([\\+\\-])(.*)$|^(.*[^\\+\\-\\*\\/\\^])([\\*\\/])(.*)$|^(.*?[^\\+\\-\\*\\/\\^])([\\^])(.*)$|^([\\+\\-])(.*)$");

    std::smatch operator_match;

    if (std::regex_search(std::cbegin(expression_str), std::cend(expression_str), operator_match, operator_regex))
    {
        if (operator_match[2].str() == "+")
        {
            Scalar lhs_arg_variant = Operators(operator_match[1].str());
            Scalar rhs_arg_variant = Operators(operator_match[3].str());

            return Scalar(new AdditionNode({lhs_arg_variant, rhs_arg_variant}));
        }
        else if (operator_match[2].str() == "-")
        {
            Scalar lhs_arg_variant = Operators(operator_match[1].str());
            Scalar rhs_arg_variant = Operators(operator_match[3].str());

            return Scalar(new SubtractionNode({lhs_arg_variant, rhs_arg_variant}));
        }
        else if (operator_match[5].str() == "*")
        {
            Scalar lhs_arg_variant = Operators(operator_match[4].str());
            Scalar rhs_arg_variant = Operators(operator_match[6].str());

            return Scalar(new MultiplicationNode({lhs_arg_variant, rhs_arg_variant}));
        }
        else if (operator_match[5].str() == "/")
        {
            Scalar lhs_arg_variant = Operators(operator_match[4].str());
            Scalar rhs_arg_variant = Operators(operator_match[6].str());

            return Scalar(new DivisionNode({lhs_arg_variant, rhs_arg_variant}));
        }
        else if (operator_match[8].str() == "^")
        {
            Scalar lhs_arg_variant = Operators(operator_match[7].str());
            Scalar rhs_arg_variant = Operators(operator_match[9].str());

            return Scalar(new PowerNode({lhs_arg_variant, rhs_arg_variant}));
        }
        else if (operator_match[10].str() == "+")
        {
            Scalar arg_variant = Operators(operator_match[11].str());

            return Scalar(new MultiplicationNode({Scalar(new NumberNode(1.0)), arg_variant}));
        }
        else if (operator_match[10].str() == "-")
        {
            Scalar arg_variant = Operators(operator_match[11].str());

            return Scalar(new MultiplicationNode({Scalar(new NumberNode(-1.0)), arg_variant}));
        }
    }

    return Nodes(expression_str);
}

Scalar ExpressionParser::Nodes(std::string const &expression_str)
{
    try
    {
        std::string loc_expression_str;
        loc_expression_str.assign(expression_str);

        loc_expression_str.erase(std::remove_if(std::begin(loc_expression_str), std::end(loc_expression_str), ::isspace), std::end(loc_expression_str));

        if (expression_str.empty())
        {
            throw std::invalid_argument("Number is empty");
        }

        std::regex real_imag_regex("^([+-]?[0-9]*\\.?[0-9]+([eE][+-]?[0-9]+)?)(i)?$");

        std::smatch real_imag_match;
        double value = 1.0;

        if (std::regex_search(std::cbegin(loc_expression_str), std::cend(loc_expression_str), real_imag_match, real_imag_regex))
        {
            if (!real_imag_match[1].str().empty())
            {
                value = std::stod(real_imag_match[1].str());
            }
        }
        else
            throw std::invalid_argument("\"" + loc_expression_str + "\" does not contain a number");

        std::string constant_name = m_parser_context->NextConstantName();

        Scalar constant_variant = Scalar(new NumberNode(value));

        m_node_map.emplace(constant_name, constant_variant);

        return constant_variant;
    }
    catch (std::invalid_argument const &)
    {
        try
        {
            return m_node_map.at(expression_str);
        }
        catch (std::out_of_range const &)
        {
            throw std::invalid_argument("No node provided for: " + expression_str);
        }
    }
}
