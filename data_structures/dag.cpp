#include "dag.h"

Dag::Dag(){}

Dag::~Dag(){ }

Dag::Dag(Triangle* triangle){
    this->triangle = triangle;
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

//setter
void Dag::setChildTwo(Dag* node){
    this->childTwo = node;
}
void Dag::setChildThree(Dag* node){
    this->childThree = node;
}

void Dag::setTriangle(Triangle* triangle){
    this->triangle = triangle;
}

//add node
void Dag::add(Dag* node, Dag* old){

    if(old->getChildOne() == nullptr){
        old->setChildOne(node);
    }

    if(old->getChildTwo() == nullptr){
        old->setChildTwo(node);
    }

    if(old->getChildTrhee() == nullptr){
        old->setChildThree(node);
    }
}
