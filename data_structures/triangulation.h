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
    std::vector<delaunay::Triangle*> getDrawTriangles();
    void addDrawTriangles(delaunay::Triangle *t);

    Triangle *createTriangle(const Point2Dd &one, const Point2Dd &two, const Point2Dd &three, Node *node, Dag *dag);
    void unionEdge(const Point2Dd &point, Node *node, Dag *dag);
protected:
    std::vector<Point2Dd> points;
    cg3::Array2D<unsigned int> triangles;
    std::vector<delaunay::Triangle*> drawTriangles;

};

}
#endif // TRIANGULATION_H
