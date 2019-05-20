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
    Triangle* e1() const;
    Triangle* e2() const;
    Triangle* e3() const;
    bool legal() const;


    //setter
    void sete1(Triangle* t);
    void sete2(Triangle* t);
    void sete3(Triangle* t);



    //funzione di stampa
    void printTriangle();

    //funzioni del triangolo
    double area();
    bool controlPointinTriangle(const cg3::Point2Dd &point);
    bool controlPointinTriangle2(const cg3::Point2Dd &point);
    bool pointIsVertex(const cg3::Point2Dd &point);
    bool operator == (const Triangle& t);
    void setLegal(const bool& legal);

    bool pointlyingontheline(const cg3::Point2Dd &p);

protected:
    Point2Dd _v1,_v2,_v3;
    bool _legal = false;
    Triangle* _e1 = nullptr;
    Triangle* _e2 = nullptr;
    Triangle* _e3 = nullptr;

};

}
#endif // TRIANGLE_H
