#ifndef NODE_H
#define NODE_H
#include "triangle.h"
using namespace delaunay;
class Node{



    protected:
    Triangle* triangle = nullptr; //informazione
    //figli, al massimo sono 3 come da slide
    Node* childOne = nullptr;
    Node* childTwo = nullptr;
    Node* childThree = nullptr;

public:
    Node();
    Node(Triangle* triangle);
    ~Node();

    Node* getChildOne() const;
    Node* getChildTwo() const;
    Node* getChildThree() const;
    Triangle* getTriangle() const;

    void setChildOne(Node* node);
    void setChildTwo(Node* node);
    void setChildThree(Node* node);
    void setTriangle(Triangle* triangle);
    //per comparare
    bool operator == (const Node& node);
    //add nodi a nodo padre
    void add(Node *node);
};

#endif // NODE_H
