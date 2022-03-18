#include "dom/Node.h"

using namespace seeker;

Node::Node(){

};

Node::~Node()
{
}

std::string Node::baseURI() const
{
    return "";
}

const std::vector<NodePtr> &Node::childNodes() const
{
    return this->_childNodes;
}

NodePtr Node::firstChild() const
{
    if (_childNodes.empty())
    {
        return nullptr;
    }
    return _childNodes.front();
}

bool Node::isConnected() const
{
    return false;
}

NodePtr Node::lastChild() const
{
    if (_childNodes.empty())
    {
        return nullptr;
    }
    return _childNodes.back();
}

NodePtr Node::nextSibling() const
{
    return _next;
}

NodePtr Node::previousSibling() const
{
    return _prev;
}

std::string Node::nodeName() const
{
    return _name;
}

int32_t Node::NodeType() const
{
    return 0;
}
std::string Node::nodeValue() const
{
    return _value;
}

void Node::setNodeValue(const std::string &value)
{
    _value = value;
}
std::string Node::textContent() const
{
    return "";
}

void Node::setTextContent(const std::string &value)
{
}

void Node::appendChild(const NodePtr &child)
{
    auto last = lastChild();
    if (last)
    {
        last->_next = child;
        child->_prev = last;
    }

    _childNodes.push_back(child);
}
NodePtr Node::cloneNode() const
{
    return nullptr;
}
bool Node::contains(const NodePtr &other)
{
    auto it = std::find(_childNodes.cbegin(), _childNodes.cend(), other);

    return it != _childNodes.end();
}
bool Node::hasChildNodes() const
{
    return !_childNodes.empty();
}

NodePtr Node::insertBefore(const NodePtr & node,const NodePtr & child)
{
    auto it = std::find(_childNodes.cbegin(), _childNodes.cend(), child);
    if(it == _childNodes.end())
    {
        return nullptr;
    }

    _childNodes.insert(it,node);

    auto prev = child->_prev;
    if(prev)
    {
        prev->_next = node;
        node->_prev = prev;
    }

    node->_next = child;
    child->_prev = node;

    return node;
}



