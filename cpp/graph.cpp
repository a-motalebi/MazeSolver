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
void Graph::preorder(Node* pn)
{
    std::cout << *pn << std::endl;
    if (pn->children.size())
        for (auto& i : pn->children)
            preorder(i);
}
void Graph::postorder(Node* pn)
{
    if (pn->children.size())
        for (auto& i : pn->children)
            preorder(i);
    std::cout << *pn << std::endl;
}
void Graph::BFS()
{
    size_t i {}, n {};
    while (n < N) {
        for (auto& j : Nodes)
            if (j->get_depth() == i) {
                std::cout << *j << std::endl;
                n++;
            }
        i++;
    }
}
