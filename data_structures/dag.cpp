#include "dag.h"
using namespace delaunay;
Dag::Dag()= default;

std::vector<Node *> Dag::nodes() { return _nodes; }

void Dag::setNodes(Node* node){ _nodes.push_back(node); }

Node* Dag::navigateGraph(const Point2Dd &point){
    bool flag = true;
    Node* root = _nodes.front();
    while(flag){
        Triangle* triangle = nullptr;
        // Se il punto si trova all'interno di questo triangolo
        //controllo che ci siano figli. Se il punto è contenuto da uno dei suoi figli, aggiorno il puntatore e ripeto il ciclo.
        if(root->first() != nullptr){
            triangle = root->first()->t();
            if(triangle->pointIsVertex(point)) return nullptr;
            if(triangle->controlPointinTriangle(point)) root = root->first();
        }

        if(root->second() != nullptr){
            triangle = root->second()->t();
            if(triangle->pointIsVertex(point)) return nullptr;
            if(triangle->controlPointinTriangle(point)) root = root->second();
        }

        if(root->third() != nullptr){
            triangle = root->third()->t();
            if(triangle->pointIsVertex(point)) return nullptr;
            if(triangle->controlPointinTriangle(point)) root = root->third();
        }
        //se non ci sono più figli si blocca il loop
       if(root->first() == nullptr && root->second() == nullptr && root->third() == nullptr)
           flag = false;

    }
    return root;
}

