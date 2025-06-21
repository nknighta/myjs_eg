#include "ast.h"
#include <utility>

// --- ElementNode ---
ElementNode::ElementNode(std::string tag_name, AttrMap attributes, NodeList children)
    : tag_name(std::move(tag_name)),
      attributes(std::move(attributes)),
      children(std::move(children)) {}

const std::string& ElementNode::get_tag_name() const {
    return tag_name;
}

const AttrMap& ElementNode::get_attributes() const {
    return attributes;
}

const NodeList& ElementNode::get_children() const {
    return children;
}

// --- TextNode ---
TextNode::TextNode(std::string text) : text(std::move(text)) {}

const std::string& TextNode::get_text() const {
    return text;
}
