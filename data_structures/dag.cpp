#include "dag.h"
using namespace delaunay;
Dag::Dag()= default;
Dag::~Dag()= default;
/**
 * @brief Dag::nodes
 * @return the vector of the nodes
 */
std::vector<Node *> Dag::nodes() { return _nodes; }
/**
 * @brief Dag::setNodes
 * @details adds the node in the vector with which I maintain the list of nodes of the dag
 * @param node
 */
void Dag::setNodes(Node* node){ _nodes.push_back(node); }

/**
 * @brief Dag::navigateGraph
 * @param point
 * @return returns the node connected to the triangle in which the point is located
 */
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
        if(root->isLeaf())
            flag = false;

    }
    return root;
}



/**
 * @brief Dag::erase
 */
void Dag::erase(){
    _nodes[0]->setFirst(nullptr);
    _nodes[0]->setSecond(nullptr);
    _nodes[0]->setThird(nullptr);
    _nodes.erase(_nodes.begin()+1, _nodes.end());
}
