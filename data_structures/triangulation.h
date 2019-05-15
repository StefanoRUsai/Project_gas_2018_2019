#ifndef TRIANGULATION_H
#define TRIANGULATION_H
#include <cg3lib/cg3/core/cg3/geometry/2d/point2d.h>
#include <cg3/data_structures/arrays/array2d.h>
#include "dag.h"
#include "node.h"
#include "triangle.h"

using namespace cg3;
namespace delaunay {


class Triangulation{

public:
    Triangulation();

protected:
    std::vector<Point2Dd> points;
    cg3::Array2D<unsigned int> triangles;

};

}
#endif // TRIANGULATION_H
