#include "delaunay.h"
#include <managers/delaunaymanager.h>
#include <utils/delaunay_checker.h>

using namespace delaunay;

Triangulation* delaunay::triangulation(const Point2Dd& BT_P1, const Point2Dd& BT_P2, const Point2Dd& BT_P3){
    Triangle* t = new Triangle(BT_P1, BT_P2, BT_P3);
    Node *node = new Node(t);
    Triangulation* tri = new Triangulation(t, node);



    return tri;
}

Triangulation* delaunay::triangulation(const std::vector<cg3::Point2Dd>& points,
                             const Point2Dd& BT_P1, const Point2Dd& BT_P2, const Point2Dd& BT_P3){
    Triangle* t = new Triangle(BT_P1, BT_P2, BT_P3);
    Node *node = new Node(t);
    Triangulation* tri = new Triangulation(t, node);

//    std::srand ( unsigned ( std::time(0) ) );
//    std::random_shuffle ( points.begin(), points.end() );

    tri->addList(points);

    return tri;
}


void delaunay::addPoint(Triangulation *tri, Point2Dd& point){

    tri->unionEdge(point);
}




