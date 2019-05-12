#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include "dag.h"
#include "node.h"
#include "triangle.h"


namespace delaunay {


class Triangulation{

public:
    Triangulation();
    std::vector<Triangle *> triangles();
    Triangulation(Triangle startTriangle);

    void setTriangles(Triangle *t);
    void createTriangle(Point2Dd* one,Point2Dd* two,Point2Dd* three, Node *node, Dag *dag);
    Triangulation(Point2Dd *one, Point2Dd *two, Point2Dd *three);
protected:
    std::vector<Triangle *> _triangles;

};

}
#endif // TRIANGULATION_H
