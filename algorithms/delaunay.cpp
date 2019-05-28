#include "delaunay.h"
#include <managers/delaunaymanager.h>
#include <utils/delaunay_checker.h>

using namespace delaunay;

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
    if(DelaunayTriangulation::Checker::isDeulaunayTriangulation(tri->points, tri->triangles)){
        std::cout<<"è giusta"<<std::endl;
    }else {
        std::cout<<"è sbagliato"<<std::endl;
    }
    return tri;
}




//void delaunay::legalizeEdge(const Point2Dd& pr, const Point2Dd& pi, const Point2Dd& pj, Triangle* tr, Dag* dag){

//}



