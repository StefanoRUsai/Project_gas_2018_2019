#include <iostream>
#include "triangle.h"
#include "dag.h"


using namespace cg3;
using namespace delaunay;
Triangle::Triangle(){}

Triangle::Triangle(const Point2Dd& vertexOne,
         const Point2Dd& vertexTwo,
         const Point2Dd& vertexThree){

        _vertexOne=vertexOne;
        _vertexTwo=vertexTwo;
        _vertexThree=vertexThree;
}
Triangle::~Triangle(){}

//getter come in java?
Point2Dd Triangle::getVertexOne() const{
    return this->_vertexOne;
}

Point2Dd Triangle::getVertexTwo() const{
    return this->_vertexTwo;
}

Point2Dd Triangle::getVertexThree() const{
    return this->_vertexThree;
}


//https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
//tecnica del baricentro
bool Triangle::controlPoint(const cg3::Point2Dd &point){

   Point2Dd one = this->getVertexOne();
   Point2Dd two = this->getVertexTwo();
   Point2Dd three = this->getVertexThree();


   double area = 0.5 *(-two.y()*three.x() + one.y()*(-two.x() + three.x()) + one.x()*(two.y() - three.y()) + two.x()*three.y());
   double s = (1/(2*area))*(one.y()*three.x() - one.x()*three.y() + (three.y() - one.y())*point.x() + (one.x() - three.x())*point.y());
   double t = (1/(2*area))*(one.x()*two.y() - one.y()*two.x() + (one.y() - two.y())*point.x() + (two.x() - one.x())*point.y());
   if(s > 0 && t > 0 && (1-s-t) > 0)
       return true;
   return false;

}

bool Triangle::pointIsVertex(const cg3::Point2Dd &point){
    if(point == this->_vertexOne)
        return true;
    if(point == this->_vertexTwo)
        return true;
    if(point == this->_vertexThree)
        return true;
    return false;
}

void Triangle::setNode(Dag* node){
    this->node = node;
}

void Triangle::printTriamgle(){
    std::cout<<"primo vertice "<<this->_vertexOne.x()<<" - "<< this->_vertexOne.y()<<std::endl;
    std::cout<<"secondo vertice "<<this->_vertexTwo.x()<<" - "<< this->_vertexTwo.y()<<std::endl;
    std::cout<<"terzo vertice "<<this->_vertexThree.x()<<" - "<< this->_vertexThree.y()<<std::endl;


}
