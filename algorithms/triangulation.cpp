#include "triangulation.h"

Triangulation::Triangulation(){}

Triangulation::~Triangulation(){}

Triangle *Triangulation::createTriangle(cg3::Point2Dd *one, cg3::Point2Dd *two, cg3::Point2Dd *three, Dag *node){
    this->triangles.push_back(new Triangle(one, two, three));
  //  this->nodes.push_back(new Dag(triangles.back()));

 //   triangles.back()->setNode(nodes.back());

 //   DagNavigation::addNode(nodes.back(), dagNodeFather);

    return triangles.back();

}

