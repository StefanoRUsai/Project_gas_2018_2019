#include "delaunay.h"
using namespace delaunay;
/*
void triangulation(std::vector<Point2Dd> points, Dag* dag, Triangulation* tri){

    for(Point2Dd point: points){
        Node* node = dag->navigateGraph(point);
        Triangle* triangle = node->t();

        tri->createTriangle(&point, triangle->v1(), triangle->v2(), node, dag);
        tri->createTriangle(&point, triangle->v2(), triangle->v3(), node, dag );
        tri->createTriangle(&point, triangle->v3(), triangle->v1(), node, dag );

    }


}
*/

Triangle* delaunay::createTriangle(const Point2Dd& one,const Point2Dd& two, const Point2Dd& three, Node *node, Dag *dag){
    Triangle* t = new Triangle(one, two, three);
    Node* n = new Node();
    n->setTriangle(t);
    dag->setNodes(n);
    node->add(n);
    return t;
}

