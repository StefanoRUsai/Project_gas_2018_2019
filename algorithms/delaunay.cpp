#include "delaunay.h"
#include <managers/delaunaymanager.h>
using namespace delaunay;

Triangulation* delaunay::triangulation(std::vector<Point2Dd>& points,
                             const Point2Dd& BT_P1, const Point2Dd& BT_P2, const Point2Dd& BT_P3){

    Triangulation* tri = new Triangulation();
    delaunay::Triangle start(BT_P1,BT_P2,BT_P3);
    Node node(&start);
    tri->addDrawTriangles(&start);
    Dag dag(&node);

    for(Point2Dd point: points){
        //Node* node = dag.navigateGraph(point);
        delaunay::Triangle *triangle = dag.navigateGraph(point)->t();

        delaunay::Triangle* tr1 = delaunay::createTriangle(point, triangle->v1(), triangle->v2(), &node, &dag);
        delaunay::Triangle* tr2 = delaunay::createTriangle(point, triangle->v2(), triangle->v3(), &node, &dag);
        delaunay::Triangle* tr3 = delaunay::createTriangle(point, triangle->v3(), triangle->v1(), &node, &dag);

        tri->addDrawTriangles(tr1);
        tri->addDrawTriangles(tr2);
        tri->addDrawTriangles(tr3);
        
        
    }
    return tri;
}


delaunay::Triangle* delaunay::createTriangle(const Point2Dd& one,const Point2Dd& two, const Point2Dd& three, Node *node, Dag *dag){
    Triangle* t = new Triangle(one, two, three);
    Node* n = new Node();
    n->setTriangle(t);
    dag->setNodes(n);
    node->add(n);
    return t;
}


//void delaunay::legalizeEdge(const Point2Dd& pr, const Point2Dd& pi, const Point2Dd& pj, Triangle* tr, Dag* dag){


//}



