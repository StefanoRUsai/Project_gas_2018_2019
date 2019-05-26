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
    Triangle *createTriangle(const Point2Dd &one, const Point2Dd &two, const Point2Dd &three, Node *node, Dag *dag);
    Triangle *createTriangle(const Point2Dd &one, const Point2Dd &two, const Point2Dd &three, Node *node1, Node *node2, Dag *dag);
    void addDrawTriangles(delaunay::Triangle *t);
    void unionEdge(const Point2Dd &point, Dag *dag);

    void subdivisionTriangle(const Point2Dd &point, Triangle *triangle, Node *node, Dag *dag);
    void subdivisionTriangleDoubleE1(const Point2Dd &point, Triangle *triangle, Node *node, Dag *dag);
    void subdivisionTriangleDoubleE2(const Point2Dd &point, Triangle *triangle, Node *node, Dag *dag);
    void subdivisionTriangleDoubleE3(const Point2Dd &point, Triangle *triangle, Node *node, Dag *dag);
    void legalizeEdge(const Point2Dd &pr, const Point2Dd &pi, const Point2Dd &pj, Triangle *t, Dag* dag);
    void edgeFlip(const Point2Dd &pr, const Point2Dd &pi, const Point2Dd &pj, Triangle *tr1, Triangle *tr2, Dag* dag);

    void AdjacencyFlip(Triangle *ntr1, Triangle *ntr2, Triangle *otr1, Triangle *otr2);
protected:

    std::vector<Point2Dd> points;
    cg3::Array2D<unsigned int> triangles;
    std::vector<delaunay::Triangle*> drawTriangles;
    int flag=0; // flag controllo costruzione triangoli nel caso di punto sulla linea

};

}
#endif // TRIANGULATION_H
