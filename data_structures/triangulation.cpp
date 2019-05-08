#include "triangulation.h"

using namespace cg3;
/*
Triangulation::Triangulation(const std::vector<cg3::Point2Dd>& listPoints, Dag* root, Triangle* startTriangle){
    this->points=listPoints;
    root->setTriangle(startTriangle);
    this->triangles.push_back(startTriangle);
    this->nodes.push_back(root);
}

Triangulation::~Triangulation(){}

void Triangulation::createTriangle(Point2Dd one,Point2Dd two,Point2Dd three, Dag *node){
    this->triangles.push_back(new Triangle(one, two, three));
    this->nodes.push_back(new Dag(triangles.back()));

    triangles.back()->setNode(nodes.back());

    node->add(nodes.back());


}
*/

//nel caso ci siano 2 nodi, controllare come evitare override della funzione
//nel caso non si possa fare un controllo sul fatto che uno dei 2 nodi non contenga l'informazione sul triangolo
/*
void Triangulation::createTriangle(Point2Dd* one,Point2Dd* two,Point2Dd* three, Dag *nodeOne, Dag *nodeTwo){
    this->triangles.push_back(new Triangle(*one, *two, *three));
    this->nodes.push_back(new Dag(triangles.back()));

    triangles.back()->setNode(nodes.back());

    nodeOne->add(nodes.back()); // triangolo padre

    nodeTwo->add(nodes.back()); //triangolo padre

}
*/


