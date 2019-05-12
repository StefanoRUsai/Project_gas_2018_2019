#include "node.h"
#include "triangulation.h"
using namespace delaunay;
Triangulation::Triangulation(){}

Triangulation::Triangulation(Triangle startTriangle){
    _triangles.push_back(&startTriangle);
}
Triangulation::Triangulation(Point2Dd* one,Point2Dd* two,Point2Dd* three){
    _triangles.push_back(new Triangle(one, two, three));
}

std::vector<Triangle *> Triangulation::triangles(){ return _triangles; }
void Triangulation::setTriangles(Triangle* t){ _triangles.push_back(t); }



void Triangulation::createTriangle(Point2Dd* one,Point2Dd* two,Point2Dd* three, Node *node, Dag *dag){
    Triangle *t= new Triangle(one, two, three);
    Node n(t);
    this->setTriangles(t);
    dag->setNodes(&n);
    node->add(&n);
}
