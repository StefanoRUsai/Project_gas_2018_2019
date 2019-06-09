#include "delaunay.h"
#include <managers/delaunaymanager.h>
#include <utils/delaunay_checker.h>

using namespace delaunay;
/*
Triangulation* delaunay::triangulation(std::vector<Point2Dd>& points,
                             const Point2Dd& BT_P1, const Point2Dd& BT_P2, const Point2Dd& BT_P3){

    Triangulation* tri = new Triangulation();
    delaunay::Triangle start(BT_P3,BT_P1,BT_P2);
    Node node(&start);
    tri->addDrawTriangles(&start);
    Dag dag(&node);

    for(Point2Dd point: points){

        tri->unionEdge(point, &dag);
    }
    tri->TrianglesForValidation();
    if(DelaunayTriangulation::Checker::isDeulaunayTriangulation(tri->getPoints(), tri->getTriangles())){
        std::cout<<"è giusta"<<std::endl;
    }else {
        std::cout<<"è sbagliato"<<std::endl;
    }
    return tri;
}
*/
/*
Triangulation *delaunay::initialization(const Point2Dd& BT_P1, const Point2Dd& BT_P2, const Point2Dd& BT_P3){
    Triangulation* tri = new Triangulation();
    delaunay::Triangle start(BT_P3,BT_P1,BT_P2);
    tri->addDrawTriangles(&start);
    tri->setDag(new Dag(new Node(&start)));

    return tri;
}
*/


Triangulation* delaunay::triangulation(std::vector<Point2Dd>& points,
                             const Point2Dd& BT_P1, const Point2Dd& BT_P2, const Point2Dd& BT_P3){
    Triangle* t = new Triangle(BT_P1, BT_P2, BT_P3);
    Node *node = new Node(t);
    Triangulation* tri = new Triangulation(t, node);

    tri->addList(points);
    return tri;
}

//void delaunay::addList(Triangulation *tri, std::vector<Point2Dd>& points){
//    for(Point2Dd point: points){

//        tri->unionEdge(point);
//    }
//}

void delaunay::addPoint(Triangulation *tri, Point2Dd& point){

    tri->unionEdge(point);
}




