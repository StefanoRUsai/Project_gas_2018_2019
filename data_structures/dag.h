#ifndef DAG_H
#define DAG_H

#include "node.h"

using namespace cg3;
using namespace std;
namespace  delaunay{

class Dag{

private:
    std::vector<Node*>* nodes = nullptr; // nodi del dag

public:
    Dag();
    Dag(Node *root);
   ~Dag();

    std::vector<Node*>* getDag() const;
    //navigazione del grafo per controllare dove si trova il punto in oggetto
    Node* navigateGraph(Node *node, const Point2Dd& point);
};

}
#endif // DAG_H
