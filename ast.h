#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>
#include <map>

// Forward declaration
class Node;

using NodePtr = std::unique_ptr<Node>;
using NodeList = std::vector<NodePtr>;
using AttrMap = std::map<std::string, std::string>;

class Node {
public:
    virtual ~Node() = default;
};

class ElementNode : public Node {
public:
    ElementNode(std::string tag_name, AttrMap attributes, NodeList children);

    const std::string& get_tag_name() const;
    const AttrMap& get_attributes() const;
    const NodeList& get_children() const;

private:
    std::string tag_name;
    AttrMap attributes;
    NodeList children;
};

class TextNode : public Node {
public:
    TextNode(std::string text);
    const std::string& get_text() const;

private:
    std::string text;
};

#endif // AST_H
