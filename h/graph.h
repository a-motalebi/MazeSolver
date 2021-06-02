#ifndef GRAPH_H
#define GRAPH_H

#include <initializer_list>
#include <iostream>
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
        void setChecked() { checked = true; };
        void setNotChecked() { checked = false; };
        bool isChecked() { return checked; };
        size_t get_depth() const { return depth; };
        void set_depth(size_t count) { depth = count; };

    private:
        size_t depth {};
        bool checked;
    };
    Graph();
    Node* root;
    Node* lastChecked;
    ~Graph();
    void show() const;
    bool isInTree(Node* n, Node* rt);

private:
    std::vector<Node*> Nodes {};
    size_t N {}; // number of Nodes
};
std::ostream& operator<<(std::ostream& os, const Graph::Node&);
#endif