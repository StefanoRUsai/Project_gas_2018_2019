#ifndef DELAUNAY_H
#define DELAUNAY_H

#include <data_structures/triangulation.h>
#include <cg3/geometry/2d/point2d.h>
using namespace cg3;

namespace delaunay {
//void triangulation(std::vector<Point2Dd>& points,
//                                       const Point2Dd& BT_P1, const Point2Dd& BT_P2, const Point2Dd& BT_P3);
Triangulation* triangulation(std::vector<Point2Dd>& points,
                   const Point2Dd& BT_P1, const Point2Dd& BT_P2, const Point2Dd& BT_P3);
Triangle* createTriangle(const Point2Dd& one,const Point2Dd& two, const Point2Dd& three, Node *node, Dag *dag);
void legalizeEdge(const Point2Dd& pr, const Point2Dd& pi, const Point2Dd& pj, Triangle* tr, Dag* dag);


}

#endif // DELAUNAY_H
