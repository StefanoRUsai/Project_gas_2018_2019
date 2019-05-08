#include "dag.h"
using namespace delaunay;
Dag::Dag(){}

Dag::~Dag(){ }


Node* Dag::navigateGraph(Node *node, const cg3::Point2Dd& point){
    bool flag = true; // se esiste un figlio deve continuare

    do{
        Triangle* triangle = nullptr;
        // Se il punto si trova all'interno di questo triangolo
        //controllo che ci siano bambini. Se il punto è contenuto da uno dei suoi figli, aggiorno il puntatore e ripeto il ciclo.
        if(node->getChildOne() != nullptr){
            triangle = node->getChildOne()->getTriangle();
            if(triangle->pointIsVertex(point)) return nullptr;
            if(triangle->controlPoint(point)){
                node = node->getChildOne();
                continue;
            }
        }

        if(node->getChildTwo() != nullptr){
            triangle = node->getChildTwo()->getTriangle();
            if(triangle->pointIsVertex(point)) return nullptr;
            if(triangle->controlPoint(point)){
                node = node->getChildTwo();
                continue;
            }
        }

        if(node->getChildThree() != nullptr){
            triangle = node->getChildTwo()->getTriangle();
            if(triangle->pointIsVertex(point)) return nullptr;
            if(triangle->controlPoint(point)){
                node = node->getChildThree();
                continue;
            }
        }

         //se non ci sono più figli si blocca il loop
        if(node->getChildOne() == nullptr && node->getChildTwo() == nullptr && node->getChildThree() == nullptr)
            flag = false;
    }while(flag != false);

    return node;
}
