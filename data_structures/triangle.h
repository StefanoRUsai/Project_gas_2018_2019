#ifndef TRIANGLE_H
#define TRIANGLE_H


#include <cg3/geometry/2d/point2d.h>

using namespace cg3;
namespace delaunay {
class Node;

/**
@brief Triangle class. This class implements a triangle using his vertex
**/

class Triangle{
public:
    //costruttori
    Triangle();
    Triangle(const Point2Dd& v1, const Point2Dd& v2, const Point2Dd& v3);
    ~Triangle();

    //getter
    Point2Dd v1() const;
    Point2Dd v2() const;
    Point2Dd v3() const;
    Triangle* e1() const;
    Triangle* e2() const;
    Triangle* e3() const;
    Node* node() const;
    bool legal() const;


    //setter
    void sete1(Triangle* t);
    void sete2(Triangle* t);
    void sete3(Triangle* t);
    void setNode(Node *node);
    void setIndex(unsigned int value);

    //print function
    void printTriangle();

    //triangle functions
    double area();
    bool controlPointinTriangle(const cg3::Point2Dd &point);
    bool controlPointinTriangle2(const cg3::Point2Dd &point);
    bool pointIsVertex(const cg3::Point2Dd &point);
    bool operator == (const Triangle& t);
    void setLegal();
    void setIllegal();

    const Point2Dd &thirdpoint(const Point2Dd &p1, const Point2Dd &p2);
    bool twoPointsAdjacent(const Point2Dd &p1, const Point2Dd &p2);
    bool isLegal();

    std::string twoPointsEdgeAdjacent(const Point2Dd &p1, const Point2Dd &p2);
    Triangle *twoPointsAdjacentTriangle(const Point2Dd &p1, const Point2Dd &p2, Triangle *t);
    void twoPointsEdgeAdjacentFlip(const Point2Dd &p1, const Point2Dd &p2, Triangle *t);
    Triangle *twoPointsAdjacentTriangleNew(const Point2Dd &p1, const Point2Dd &p2);
    Triangle *PointsAdjacent(const Point2Dd &p1, const Point2Dd &p2);
    Triangle *searchAdjacentTriangle(const Point2Dd &p1, const Point2Dd &p2);
    bool pointLyingOnTheLineCheck(const Point2Dd &p, const Point2Dd &a, const Point2Dd &b);

protected:

    Point2Dd _v1,_v2,_v3; // vertex of triangle
    bool _legal; // check if the triangle is legal
    Triangle* _e1 = nullptr; //Pointer to adjacent triangle for edge 1
    Triangle* _e2 = nullptr; //Pointer to adjacent triangle for edge 1
    Triangle* _e3 = nullptr; //Pointer to adjacent triangle for edge 3
    delaunay::Node* _node = nullptr; // cross link between triangle and node
};

}
#endif // TRIANGLE_H
