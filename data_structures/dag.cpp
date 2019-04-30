#include "dag.h"

Dag::Dag(){}

Dag::~Dag(){ }

Dag::Dag(Triangle* tr){
    this->tr = tr;
}

//getter
Dag* Dag::getChildOne() const{
    return this->childOne;
}

Dag* Dag::getChildTwo() const{
    return this->childTwo;
}

Dag* Dag::getChildTrhee() const{
    return this->childThree;
}

Triangle* Dag::getTriangle() const{
    return this->triangle;
}

void Dag::setChildOne(Dag* node){
    this->childOne = node;
}

void Dag::setChildTwo(Dag* node){
    this->childTwo = node;
}
void Dag::setChildThree(Dag* node){
    this->childThree = node;
}

void Dag::setTriangle(Triangle* triangle){
    this->triangle = triangle;
}
