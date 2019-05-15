#ifndef TRIANGLE_H
#define TRIANGLE_H


#include <cg3/geometry/2d/point2d.h>
using namespace cg3;
namespace delaunay {

class Triangle{
public:
    //costruttori
    Triangle();
    Triangle(const Point2Dd& v1, const Point2Dd& v2, const Point2Dd& v3);

    //getter
    Point2Dd v1() const;
    Point2Dd v2() const;
    Point2Dd v3() const;


    //funzione di stampa
    void printTriangle();

    //funzioni del triangolo
    double area();
    bool controlPointinTriangle(const cg3::Point2Dd &point);
    bool controlPointinTriangle2(const cg3::Point2Dd &point);
    bool pointIsVertex(const cg3::Point2Dd &point);
    bool operator == (const Triangle& t);

protected:
    Point2Dd _v1,_v2,_v3;

};

}
#endif // TRIANGLE_H
