#ifndef DELAUNAY_H
#define DELAUNAY_H

#include <data_structures/triangulation.h>


namespace delaunay {

void triangulation(std::vector<Point2Dd> points, Dag* dag, Triangulation* tri);
Triangle* createTriangle(const Point2Dd& one,const Point2Dd& two, const Point2Dd& three, Node *node, Dag *dag);



}

#endif // DELAUNAY_H
