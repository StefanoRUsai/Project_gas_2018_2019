#include <iostream>
#include "triangle.h"
#include "node.h"
using namespace delaunay;


Triangle::Triangle(const Point2Dd& v1, const  Point2Dd& v2,const  Point2Dd& v3){
    _v1=v1;
    _v2=v2;
    _v3=v3;
    _legal=true;
}

Point2Dd Triangle::v1() const{
    return _v1;}
Point2Dd Triangle::v2() const{
    return _v2;}
Point2Dd Triangle::v3() const{
    return _v3;}
Triangle* Triangle::e1() const{ return _e1; }
Triangle* Triangle::e2() const{ return _e2; }
Triangle* Triangle::e3() const{ return _e3; }
Node* Triangle::node() const{ return _node; }

double Triangle::area(){
    return (0.5 * (-_v2.y() * _v3.x() + _v1.y() * (-_v2.x() + _v3.x()) + _v1.x()*(_v2.y() - _v3.y()) + _v2.x()*_v3.y()));
}

//setter
void Triangle::sete1(Triangle *t){ _e1=t; }
void Triangle::sete2(Triangle *t){ _e2=t; }
void Triangle::sete3(Triangle *t){ _e3=t; }
void Triangle::setNode(Node *node){ _node=node; }

//https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
//tecnica del baricentro

bool Triangle::controlPointinTriangle(const cg3::Point2Dd &p){

double a = area();
double s = (1/(2*a))*(_v1.y()*_v3.x() - _v1.x()*_v3.y() + (_v3.y() - _v1.y())*p.x() + (_v1.x() - _v3.x())*p.y());
double t = (1/(2*a))*(_v1.x()*_v2.y() - _v1.y()*_v2.x() + (_v1.y() - _v2.y())*p.x() + (_v2.x() - _v1.x())*p.y());
return s > 0 && t > 0 && (1-s-t) > 0;
}

bool Triangle::controlPointinTriangle2(const cg3::Point2Dd &p){
    double as_x = p.x()-_v1.x();
    double as_y = p.y()-_v1.y();

    bool s_ab = (_v2.x()-_v1.x())*as_y-(_v2.y()-_v1.y())*as_x > 0;

    if((_v3.x()-_v1.x())*as_y-(_v3.y()-_v1.y())*as_x > 0 == s_ab) return false;

    if((_v3.x()-_v2.x())*(p.y()-_v2.y())-(_v3.y()-_v2.y())*(p.x()-_v2.x()) > 0 != s_ab) return false;

    return true;
}

bool Triangle::pointIsVertex(const cg3::Point2Dd &point){
    if(point == _v1) return true;
    if(point == _v2) return true;
    if(point == _v3) return true;

    return false;
}

void Triangle::printTriangle(){
    std::cout<<"vertex one "<<_v1.x()<<","<<_v1.y()<<std::endl;
    std::cout<<"vertex two "<<_v2.x()<<","<<_v2.y()<<std::endl;
    std::cout<<"vertex three "<<_v3.x()<<","<<_v3.y()<<std::endl;
}
bool Triangle::operator == (const Triangle& t){ return (_v1 == t.v1() && _v2 == t.v2() && _v3 == t.v3()); }

void Triangle::setLegal(){
    _legal=true;
}
void Triangle::setIllegal(){
    _legal=false;
}
bool Triangle::isLegal(){return _legal;}


const Point2Dd& Triangle::thirdpoint(const Point2Dd& p1, const Point2Dd& p2){
    if ((_v2 == p1 && _v3 == p2)||(_v3 == p1 && _v2 == p2)) return _v1;
    if ((_v3 == p1 && _v1 == p2)||(_v1 == p1 && _v3 == p2)) return _v2;
    if ((_v1 == p1 && _v2 == p2)||(_v2 == p1 && _v1 == p2)) return _v3;

    return p1;

}

bool Triangle::twoPointsAdjacent(const Point2Dd& p1, const Point2Dd& p2){
    if ((_v2 == p1 && _v3 == p2)||(_v3 == p1 && _v2 == p2)) return true;
    if ((_v3 == p1 && _v1 == p2)||(_v1 == p1 && _v3 == p2)) return true;
    if ((_v1 == p1 && _v2 == p2)||(_v2 == p1 && _v1 == p2)) return true;
    return false;
}



void Triangle::twoPointsEdgeAdjacentFlip(const Point2Dd& p1, const Point2Dd& p2, Triangle* t){
    if ((_v2 == p1 && _v3 == p2)||(_v3 == p1 && _v2 == p2)){
        if (t != nullptr)
            this->sete2(t);
    }
    if ((_v3 == p1 && _v1 == p2)||(_v1 == p1 && _v3 == p2)){
        if (t != nullptr)
            this->sete3(t);
    }
    if ((_v1 == p1 && _v2 == p2)||(_v2 == p1 && _v1 == p2)){
        if (t != nullptr)
           this->sete1(t);
    }

}

Triangle* Triangle::PointsAdjacent(const Point2Dd& p1, const Point2Dd& p2){


    if ((v2() == p1 && v3() == p2)||(v3() == p1 && v2() == p2)){
        if (e2()!= nullptr) return e2();
    }

    if ((v3() == p1 && v1() == p2)||(v1() == p1 && v3() == p2)){
        if (e3()!= nullptr) return e3();
    }

    if ((v1() == p1 && v2() == p2)||(v2() == p1 && v1() == p2)){
        if (e1()!= nullptr) return e1();
    }
    return nullptr;

}

Triangle* Triangle::searchAdjacentTriangle(const Point2Dd& p1, const Point2Dd& p2){


    if(e1()!=nullptr)
        return e1()->PointsAdjacent(p1,p2);

    if(e2()!=nullptr)
        return e2()->PointsAdjacent(p1,p2);

    if(e3()!=nullptr)
        return e3()->PointsAdjacent(p1,p2);

    return nullptr;

}
