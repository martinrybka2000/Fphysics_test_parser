
#pragma once

#include <memory>
#include <cmath>

#include "node.hpp"

class CosNode : public Node
{
public:
    CosNode(std::initializer_list<Scalar> const &arguments);
    virtual ~CosNode() {}

    std::string Type() const override;

    double Value() const override;
};

class SinNode : public Node
{
public:
    SinNode(std::initializer_list<Scalar> const &arguments);
    virtual ~SinNode() {}

    std::string Type() const override;

    double Value() const override;
};

class TanNode : public Node
{
public:
    TanNode(std::initializer_list<Scalar> const &arguments);
    virtual ~TanNode() {}

    std::string Type() const override;

    double Value() const override;
};

class AcosNode : public Node
{
public:
    AcosNode(std::initializer_list<Scalar> const &arguments);
    virtual ~AcosNode() {}

    std::string Type() const override;

    double Value() const override;
};

class AsinNode : public Node
{
public:
    AsinNode(std::initializer_list<Scalar> const &arguments);
    virtual ~AsinNode() {}

    std::string Type() const override;

    double Value() const override;
};

class AtanNode : public Node
{
public:
    AtanNode(std::initializer_list<Scalar> const &arguments);
    virtual ~AtanNode() {}

    std::string Type() const override;

    double Value() const override;
};

class SqrtNode : public Node
{
public:
    SqrtNode(std::initializer_list<Scalar> const &arguments);
    virtual ~SqrtNode() {}

    std::string Type() const override;

    double Value() const override;
};

class AbsNode : public Node
{
public:
    AbsNode(std::initializer_list<Scalar> const &arguments);
    virtual ~AbsNode(){}

    std::string Type() const override;

    double Value() const override;
};

class ExpNode : public Node
{
public:
    ExpNode(std::initializer_list<Scalar> const &arguments);
    virtual ~ExpNode(){}

    std::string Type() const override;

    double Value() const override;
};

class LnNode : public Node
{
public:
    LnNode(std::initializer_list<Scalar> const &arguments);
    virtual ~LnNode() {}

    std::string Type() const override;

    double Value() const override;
};
