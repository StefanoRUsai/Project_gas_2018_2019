#ifndef NODE_H
#define NODE_H
#include <data_structures/triangle.h>

namespace delaunay  {
/**
 * @brief Class for representing a Node. Every node has 3 children.
 */

class Node{
public:
    //costruttore
    Node();
    Node(Triangle* t);

    //getter
    Triangle* t() const;
    Node* first() const;
    Node* second() const;
    Node* third() const;

    //setter
    void setTriangle(Triangle* t);
    void setFirst(Node* node);
    void setSecond(Node* node);
    void setThird(Node* node);

    //add child
    void add(Node* node);

    //compere
    bool operator ==(const Node& node);

protected:
    Triangle* _t = nullptr; //info
    Node* _first = nullptr; // first child
    Node* _second = nullptr; // second child
    Node* _third = nullptr; // third child

};

}

#endif // NODE_H
