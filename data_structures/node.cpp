#include "node.h"

Node::Node(){}

Node::~Node(){}

Node::Node(Triangle* triangle){
    this->triangle = triangle;
}

//getter
Node* Node::getChildOne() const{
    return this->childOne;
}

Node* Node::getChildTwo() const{
    return this->childTwo;
}

Node* Node::getChildThree() const{
    return this->childThree;
}

Triangle* Node::getTriangle() const{
    return this->triangle;
}

void Node::setChildOne(Node* node){
    this->childOne = node;
}

//setter
void Node::setChildTwo(Node* node){
    this->childTwo = node;
}
void Node::setChildThree(Node* node){
    this->childThree = node;
}

void Node::setTriangle(Triangle* triangle){
    this->triangle = triangle;
}

bool Node::operator == (const Node& node){
    return (this->triangle == node.getTriangle());
}


//add node
void Node::add(Node* node){

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
