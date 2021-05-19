#ifndef GRAPH_H
#define GRAPH_H
// #include "maze.h"
#include <compare>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Graph {
public:
    friend class Maze;
    class Node {
    public:
        double value;
        Node* parent;
        std::vector<Node*> children;
        Node();
        explicit Node(double);
        Node(double value, Node* parent);
        size_t get_depth() const { return depth; };
        void set_depth(size_t count) { depth = count; };
        std::partial_ordering operator<=>(const Node& n) const { return value <=> n.value; };
        bool operator==(const Node& n) const { return value == n.value; };

    private:
        size_t depth {};
    };
    Graph();
    Node* root;
    ~Graph();
    void show() const;
    void preorder(Node*);
    void postorder(Node*);
    void BFS();

private:
    std::vector<Node*> Nodes {};
    size_t N {}; // number of Nodes
};
std::ostream& operator<<(std::ostream& os, const Graph::Node&);
#endif