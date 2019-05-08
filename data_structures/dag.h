#ifndef DAG_H
#define DAG_H

#include "node.h"

using namespace cg3;
namespace  delaunay{

class Dag{

public:
    Dag();
   ~Dag();
    std::vector<Node> nodes; // nodi del dag
    //navigazione del grafo per controllare dove si trova il punto in oggetto
    Node* navigateGraph(Node *node, const Point2Dd& point);
    //controllo se il punto è contenuto dentro il triangolo
};

}
#endif // DAG_H
