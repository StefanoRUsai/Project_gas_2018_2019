#ifndef DAG_H
#define DAG_H

#include <iostream>
#include "node.h"

namespace delaunay {
/**
 * @brief Class for representing a Directed acyclic graph
 */
class Dag{

public:
    Dag();
    ~Dag();
    //getter
    std::vector<Node *> nodes();
    Node* navigateGraph(const Point2Dd &point);
    Node *navigateforFlip(const Point2Dd &point1, const Point2Dd &point2);
    void setNodes(Node* node);
    void erase();

protected:

    std::vector<Node *> _nodes; // vector of nodes
};
}


#endif // DAG_H
