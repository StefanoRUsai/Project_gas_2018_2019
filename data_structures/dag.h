#ifndef DAG_H
#define DAG_H

#include <iostream>
#include "node.h"

namespace delaunay {
class Dag{

public:
    Dag();
    Dag(Node *root);


    //getter
    std::vector<Node *> nodes();
    //navigazione del grafo secondo tentativo, vediamo se implode tutto
    Node* navigateGraph(const Point2Dd& poin);
    void setNodes(Node* node);

protected:
    //non è un puntatore ma è composto da puntatori a nodi
    //usato al posto della lista perchè molto più veloce
    std::vector<Node *> _nodes;
};
}


#endif // DAG_H
