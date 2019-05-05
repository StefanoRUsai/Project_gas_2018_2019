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

Dag* Dag::getChildThree() const{
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

bool Dag::operator == (const Dag& node){
    return (this->triangle == node.getTriangle());
}


//add node
void Dag::add(Dag* node){

    if(this->getChildOne() == nullptr){
       this->setChildOne(node);
       return;
    }

    if(this->getChildTwo() == nullptr){
        this->setChildTwo(node);
        return;
    }

    if(this->getChildThree() == nullptr){
        this->setChildThree(node);
        return;
    }
}

Dag* Dag::navigateGraph(const cg3::Point2Dd& point){
    bool flag = true; // se esiste un figlio deve continuare

    do{

        if(this == nullptr)
            return nullptr;


        Triangle* t = nullptr;

        // Se il punto si trova all'interno di questo triangolo
        //controllo che ci siano bambini. Se il punto è contenuto da uno dei suoi figli, aggiorno il puntatore e ripeto il ciclo.
        if(this->getChildOne() != nullptr){
            t = this->getChildOne()->getTriangle();

            if(t->pointIsVertex(point))
                return nullptr;

            if(t->controlPoint(point)){
                this->childOne = this->getChildOne()->getChildOne();
                this->childTwo = this->getChildOne()->getChildTwo();
                this->childThree= this->getChildOne()->getChildThree();
                this->triangle = this->getChildOne()->getTriangle();
                continue;
            }
        }

        if(this->getChildTwo() != nullptr){
            t = this->getChildTwo()->getTriangle();

            if(t->pointIsVertex(point))
                return nullptr;

            if(t->controlPoint(point)){
                this->childOne = this->getChildTwo()->getChildOne();
                this->childTwo = this->getChildTwo()->getChildTwo();
                this->childThree= this->getChildTwo()->getChildThree();
                this->triangle = this->getChildTwo()->getTriangle();
                continue;
            }
        }

        if(this->getChildThree() != nullptr){
            t = this->getChildTwo()->getTriangle();

            if(t->pointIsVertex(point))
                return nullptr;

            if(t->controlPoint(point)){
                this->childOne = this->getChildTwo()->getChildOne();
                this->childTwo = this->getChildTwo()->getChildTwo();
                this->childThree= this->getChildTwo()->getChildThree();
                this->triangle = this->getChildTwo()->getTriangle();
                continue;
            }
        }

         //se non ci sono più figli si blocca il loop
        if(this->getChildOne() == nullptr && this->getChildTwo() == nullptr && this->getChildThree() == nullptr)
            flag = false;
    }while(flag != false);

    return this;
}
