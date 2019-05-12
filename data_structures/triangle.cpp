#include <iostream>
#include "triangle.h"
using namespace delaunay;
Triangle::Triangle(Point2Dd* v1, Point2Dd* v2, Point2Dd* v3){
    _v1=v1;
    _v2=v2;
    _v3=v3;
}

Point2Dd* Triangle::v1() const{
    return _v1;}
Point2Dd* Triangle::v2() const{
    return _v2;}
Point2Dd* Triangle::v3() const{
    return _v3;}

double Triangle::area(){
    return (0.5 * (-_v2->y()*_v3->x() + _v1->y()*(-_v2->x() + _v3->x()) + _v1->x()*(_v2->y() - _v3->y()) + _v2->x()*_v3->y()));
}

//https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
//tecnica del baricentro

bool Triangle::controlPointinTriangle(const cg3::Point2Dd &p){

double a = area();
double s = (1/(2*a))*(_v1->y()*_v3->x() - _v1->x()*_v3->y() + (_v3->y() - _v1->y())*p.x() + (_v1->x() - _v3->x())*p.y());
double t = (1/(2*a))*(_v1->x()*_v2->y() - _v1->y()*_v2->x() + (_v1->y() - _v2->y())*p.x() + (_v2->x() - _v1->x())*p.y());
if(s > 0 && t > 0 && (1-s-t) > 0)
   return true;

return false;
}

bool Triangle::controlPointinTriangle2(const cg3::Point2Dd &p){
    double as_x = p.x()-_v1->x();
    double as_y = p.y()-_v1->y();

    bool s_ab = (_v2->x()-_v1->x())*as_y-(_v2->y()-_v1->y())*as_x > 0;

    if((_v3->x()-_v1->x())*as_y-(_v3->y()-_v1->y())*as_x > 0 == s_ab) return false;

    if((_v3->x()-_v2->x())*(p.y()-_v2->y())-(_v3->y()-_v2->y())*(p.x()-_v2->x()) > 0 != s_ab) return false;

    return true;
}

bool Triangle::pointIsVertex(const cg3::Point2Dd &point){
    if(point == *_v1) return true;
    if(point == *_v2) return true;
    if(point == *_v3) return true;

    return false;
}

void Triangle::printTriangle(){
    std::cout<<"vertex one "<<_v1->x()<<","<<_v1->y()<<std::endl;
    std::cout<<"vertex two "<<_v2->x()<<","<<_v2->y()<<std::endl;
    std::cout<<"vertex three "<<_v3->x()<<","<<_v3->y()<<std::endl;
}

