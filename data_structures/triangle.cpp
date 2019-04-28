#include "triangle.h"

Triangle::Triangle(){}

Triangle::Triangle(cg3::Point2Dd* vertexOne,
         cg3::Point2Dd* vertexTwo,
         cg3::Point2Dd* vertexThree){
    this->vertexOne = vertexOne;
    this->vertexTwo = vertexTwo;
    this->vertexThree = vertexThree;

}
Triangle::~Triangle(){}

//getter come in java?
cg3::Point2Dd* Triangle::getVertexOne() const{
    return this->vertexOne;
}

cg3::Point2Dd* Triangle::getVertexTwo() const{
    return this->vertexTwo;
}

cg3::Point2Dd* Triangle::getVertexThree() const{
    return this->vertexThree;
}


Triangle* Triangle::getAdjacentOne() const{
   return this->adjacentOne;
}

Triangle* Triangle::getAdjacentTwo() const{
   return this->adjacentTwo;
}

Triangle* Triangle::getAdjacentThree() const{
   return this->adjacentThree;
}



//setter
void Triangle::setVertexOne(cg3::Point2Dd* vertexOne){
    this->vertexOne = vertexOne;
}

void Triangle::setVertexTwo(cg3::Point2Dd* vertexTwo){
    this->vertexTwo = vertexTwo;
}

void Triangle::setVertexThree(cg3::Point2Dd* vertexThree){
    this->vertexThree = vertexThree;
}

void Triangle::setAdjacentOne(Triangle* adjacentOne){
    this->adjacentOne = adjacentOne;
}

void Triangle::setAdjacentTwo(Triangle* adjacentTwo){
    this->adjacentTwo = adjacentTwo;
}
void Triangle::setAdjacentThree(Triangle* adjacentThree){
    this->adjacentThree = adjacentThree;
}
