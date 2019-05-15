#ifndef NODE_H
#define NODE_H
#include <data_structures/triangle.h>

namespace delaunay  {
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
    Triangle* _t=nullptr;
    Node* _first = nullptr;
    Node* _second = nullptr;
    Node* _third = nullptr;

};

}

#endif // NODE_H
