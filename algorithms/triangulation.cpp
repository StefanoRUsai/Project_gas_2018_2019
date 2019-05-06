#include "triangulation.h"

using namespace cg3;
Triangulation::Triangulation(){}

Triangulation::~Triangulation(){}

Triangle *Triangulation::createTriangle(Point2Dd* one,Point2Dd* two,Point2Dd* three, Dag *node){
    this->triangles.push_back(new Triangle(*one, *two, *three));
    this->nodes.push_back(new Dag(triangles.back()));

 //   triangles.back()->setNode(nodes.back());

 //   DagNavigation::addNode(nodes.back(), dagNodeFather);

    return triangles.back();

}

