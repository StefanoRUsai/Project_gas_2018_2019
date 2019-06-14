#include "node.h"
using namespace delaunay;
Node::Node()= default;


Node::Node(Triangle* t){ _t= t;}

//getter
Triangle* Node::t() const { return _t; }
Node* Node::first() const{ return _first; }
Node* Node::second() const{ return _second; }
Node* Node::third() const{ return _third; }

//setter
void Node::setTriangle (Triangle* t){ _t=t; }
void Node::setFirst(Node* node){ _first=node; }
void Node::setSecond(Node* node){ _second=node; }
void Node::setThird(Node* node){ _third=node; }

//funzioni nodo
bool Node::operator == (const Node& node){ return (_t == node.t()); }

//add child

void Node::add(Node* node){

    if(this->first() == nullptr){
       this->setFirst(node);
       return;
    }

    if(this->second() == nullptr){
        this->setSecond(node);
        return;
    }

    if(this->third() == nullptr){
        this->setThird(node);
        return;
    }
}
