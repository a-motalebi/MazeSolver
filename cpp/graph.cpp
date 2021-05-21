#include "graph.h"

Graph::Node::Node(double _value)
    : value { _value }
    , parent { nullptr }
    , children {}
{
}
Graph::Node::Node(double _value, Node* _parent)
    : value { _value }
    , parent { _parent }
{
    parent->children.push_back(this);
    depth = parent->get_depth() + 1;
}
std::ostream& operator<<(std::ostream& os, const Graph::Node& node)
{
    os << "(value:" << node.value << ", parent:";
    if (node.parent == nullptr)
        os << " ";
    else
        os << node.parent->value;
    os << ", depth:" << node.get_depth() << ")";
    return os;
}
////////////////////////////////////////////
////////////////////////////////////////////
Graph::Graph()
{
}
Graph::~Graph()
{
    for (auto& i : Nodes)
        delete i;
}
void Graph::show() const
{
    std::cout << "This Graph Nodes:" << std::endl;
    for (auto& i : Nodes)
        std::cout << *i << std::endl;
}
bool Graph::isInTree(Node* n, Node* rt)
{
    if (!n || !rt)
        return false;
    do {
        if (n->parent == rt || n == rt)
            return true;
        n = n->parent;
    } while (n != nullptr);
    return false;
}