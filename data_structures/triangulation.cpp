#include "node.h"
#include "triangulation.h"
#include "triangle.h"

using namespace delaunay;
Triangulation::Triangulation(){}


std::vector<delaunay::Triangle*> Triangulation::getDrawTriangles(){
    return drawTriangles;
}

void Triangulation::addDrawTriangles(delaunay::Triangle* t){
    drawTriangles.push_back(t);
}

void Triangulation::unionEdge(const Point2Dd& point, Node* node, Dag* dag){
    delaunay::Triangle *triangle = dag->navigateGraph(point)->t();

    delaunay::Triangle* tr1 = Triangulation::createTriangle(point, triangle->v1(), triangle->v2(), node, dag);
    delaunay::Triangle* tr2 = Triangulation::createTriangle(point, triangle->v2(), triangle->v3(), node, dag);
    delaunay::Triangle* tr3 = Triangulation::createTriangle(point, triangle->v3(), triangle->v1(), node, dag);

    this->addDrawTriangles(tr1);
    this->addDrawTriangles(tr2);
    this->addDrawTriangles(tr3);
}

Triangle* Triangulation::createTriangle(const Point2Dd& one,const Point2Dd& two, const Point2Dd& three, Node *node, Dag *dag){
    Triangle* t = new Triangle(one, two, three);
    Node* n = new Node();
    n->setTriangle(t);
    dag->setNodes(n);
    node->add(n);
    return t;
}
