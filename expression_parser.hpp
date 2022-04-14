#pragma once

#include <exception>
#include <memory>
#include <string>
#include <map>
#include <algorithm>
#include <regex>
#include <iostream>

#include "node.hpp"
#include "operations.hpp"
#include "functions.hpp"

class ExpressionParserContext
{
    friend class ExpressionParser;

    uint32_t m_expression_id;
    uint32_t m_function_id;
    uint32_t m_constant_id;
    uint32_t m_matrix_id;

public:
    static std::shared_ptr<ExpressionParserContext> const default_context;

    ExpressionParserContext();

private:
    std::string NextExpressionName();
    std::string NextFunctionName();
    std::string NextConstantName();
    std::string NextMatrixName();
};

class ExpressionParser
{
    std::string m_expression_str;

    std::map<std::string, Scalar> m_node_map;

    std::shared_ptr<ExpressionParserContext> m_parser_context;

    ExpressionParser(std::string const &expression_str, std::map<std::string, Scalar> const &node_map, std::shared_ptr<ExpressionParserContext> const &parser_context, bool const &clean_and_verify);

public:
    ExpressionParser(std::string const &expression_str, std::map<std::string, Scalar> const &node_map = {}, std::shared_ptr<ExpressionParserContext> const &parser_context = ExpressionParserContext::default_context);

    Scalar Parse();

private:
    void Clean();
    void Verify();

    Scalar Brackets(std::string const &expression_str);
    Scalar Functions(std::string const &expression_str);
    Scalar Operators(std::string const &expression_str);
    Scalar Nodes(std::string const &expression_str);
};
