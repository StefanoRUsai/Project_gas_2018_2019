#ifndef DELAUNAY_H
#define DELAUNAY_H

#include <data_structures/triangulation.h>
#include <cg3/geometry/2d/point2d.h>
using namespace cg3;

namespace delaunay {

Triangulation* triangulation(const std::vector<Point2Dd> &points,
                             const Point2Dd& BT_P1, const Point2Dd& BT_P2, const Point2Dd& BT_P3);

Triangulation* triangulation(const Point2Dd& BT_P1, const Point2Dd& BT_P2, const Point2Dd& BT_P3);


}

#endif // DELAUNAY_H
