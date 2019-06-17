#ifndef VORONOI_H
#define VORONOI_H

#include <data_structures/triangulation.h>
#include <cg3/geometry/2d/point2d.h>

using namespace cg3;
using namespace delaunay;
namespace voronoi {

Point2Dd circumcircle(Triangle*);

}
#endif // VORONOI_H
