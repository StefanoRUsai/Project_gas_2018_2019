#include "triangle.h"
#include "dag.h"


using namespace cg3;
Triangle::Triangle(){}

Triangle::Triangle(const Point2Dd& vertexOne,
         const Point2Dd& vertexTwo,
         const Point2Dd& vertexThree){
    this->vertexOne = vertexOne;
    this->vertexTwo = vertexTwo;
    this->vertexThree = vertexThree;

}
Triangle::~Triangle(){}

//getter come in java?
cg3::Point2Dd Triangle::getVertexOne() const{
    return this->vertexOne;
}

cg3::Point2Dd Triangle::getVertexTwo() const{
    return this->vertexTwo;
}

cg3::Point2Dd Triangle::getVertexThree() const{
    return this->vertexThree;
}




//setter
void Triangle::setVertexOne(cg3::Point2Dd* vertexOne){
    this->vertexOne = *vertexOne;
}

void Triangle::setVertexTwo(cg3::Point2Dd* vertexTwo){
    this->vertexTwo = *vertexTwo;
}

void Triangle::setVertexThree(cg3::Point2Dd* vertexThree){
    this->vertexThree = *vertexThree;
}



//https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
//tecnica del baricentro
bool Triangle::controlPoint(const cg3::Point2Dd &point){

   cg3::Point2Dd one = this->getVertexOne();
   cg3::Point2Dd two = this->getVertexTwo();
   cg3::Point2Dd three = this->getVertexThree();


   double area = 0.5 *(-two.y()*three.x() + one.y()*(-two.x() + three.x()) + one.x()*(two.y() - three.y()) + two.x()*three.y());

   double s = (1/(2*area))*(one.y()*three.x() - one.x()*three.y() + (three.y() - one.y())*point.x() + (one.x() - three.x())*point.y());

   double t = (1/(2*area))*(one.x()*two.y() - one.y()*two.x() + (one.y() - two.y())*point.x() + (two.x() - one.x())*point.y());

   if(s > 0 && t > 0 && (1-s-t) > 0)
       return true;

    return false;

}

bool Triangle::pointIsVertex(const cg3::Point2Dd &point){
    if(point == this->vertexOne)
        return true;
    if(point == this->vertexTwo)
        return true;
    if(point == this->vertexThree)
        return true;
    return false;
}

void Triangle::setNode(Dag* node){
    this->node = node;
}
