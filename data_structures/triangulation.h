#ifndef TRIANGULATION_H
#define TRIANGULATION_H
#include <cg3lib/cg3/core/cg3/geometry/2d/point2d.h>
#include <cg3/data_structures/arrays/array2d.h>
#include "dag.h"
#include "node.h"
#include "triangle.h"

using namespace cg3;
namespace delaunay {

/**
 * @brief Class for representing a triangulation
 * The class consists of a vector of triangles, a vector of points, a matrix with the points of triangles and a DAG field.
 * This class deals with the creation of new triangles, after the addition of points, for all 2 cases that requires the delaunay
 * agorhythm, i.e. both if the point is inside the triangle and when the point falls on the line.
 * It also takes care of checking that the triangulation is legal and in case it is not, it uses the required flip technique.
 */
class Triangulation{

public:
    Triangulation();
    ~Triangulation();
    Triangulation(const Point2Dd &BT_P1, const Point2Dd &BT_P2, const Point2Dd &BT_P3);
    Triangulation(Triangle *t, Node *node);
    std::vector<delaunay::Triangle*> getDrawTriangles();

    //create triangles
    Triangle *createTriangle(const Point2Dd &one, const Point2Dd &two, const Point2Dd &three, Node *node, Dag *dag);
    Triangle *createTriangle(const Point2Dd &one, const Point2Dd &two, const Point2Dd &three, Node *node1, Node *node2, Dag *dag);
    void addDrawTriangles(delaunay::Triangle *t);
    void unionEdge(const Point2Dd &point);
    void setDag(Dag* dag);

    //insert point
    void addList(const std::vector<Point2Dd> &points);
    void addPoint(Point2Dd &point);

    //subdivision
    void subdivisionTriangle(const Point2Dd &point, Triangle *triangle, Node *node, Dag *dag);
    void subdivisionTriangleDoubleE1(const Point2Dd &point, Triangle *triangle, Node *node, Dag *dag);
    void subdivisionTriangleDoubleE2(const Point2Dd &point, Triangle *triangle, Node *node, Dag *dag);
    void subdivisionTriangleDoubleE3(const Point2Dd &point, Triangle *triangle, Node *node, Dag *dag);

    // legalization
    void legalizeEdge(const Point2Dd &pr, const Point2Dd &pi, const Point2Dd &pj, Triangle *t, Dag* dag);
    void edgeFlip(const Point2Dd &pr, const Point2Dd &pi, const Point2Dd &pj, Triangle *tr1, Triangle *tr2, Dag* dag);

    void TrianglesForValidation();
    std::vector<Point2Dd> getPoints();
    void setPoints(const Point2Dd& p);
    cg3::Array2D<unsigned int> getTriangles();
    void setTriangles(int index, int c, unsigned int position);

    void resizeTriangles(int row, int colum);


    void eraseTriangulation();

protected:

    std::vector<Point2Dd> _points; // vector of points belonging of the triangle
    cg3::Array2D<unsigned int> _triangles; // matrix of triangles
    std::vector<delaunay::Triangle*> drawTriangles; // vector of triangles to be printed
    Dag _dag;

};

}
#endif // TRIANGULATION_H
