#include "node.h"
using namespace delaunay;
Node::Node()=default;
Node::~Node()=default;
/**
 * @brief Node::Node
 * @param t
 */
Node::Node(Triangle* t){ _t= t;}

//getter
/**
 * @brief Node::t
 * @details returns the triangle from the node
 * @return _t
 */
Triangle* Node::t() const { return _t; }
/**
 * @brief Node::first
 * @return first
 */
Node* Node::first() const{ return _first; }
/**
 * @brief Node::second
 * @return second
 */
Node* Node::second() const{ return _second; }
/**
 * @brief Node::third
 * @return third
 */
Node* Node::third() const{ return _third; }

//setter
void Node::setTriangle (Triangle* t){ _t=t; }
/**
 * @brief Node::setFirst
 * @param node
 */
void Node::setFirst(Node* node){ _first=node; }
/**
 * @brief Node::setSecond
 * @param node
 */
void Node::setSecond(Node* node){ _second=node; }
/**
 * @brief Node::setThird
 * @param node
 */
void Node::setThird(Node* node){ _third=node; }

//funzioni nodo
/**
 * @brief Node::operator ==
 * @details checks if the triangle of the node is equal
 * @param node
 * @return
 */
bool Node::operator == (const Node& node){ return (_t == node.t()); }

//add child
/**
 * @brief Node::add
 * @details adds children to nodes
 * @param node
 */
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

bool Node::isLeaf(){
    if (this->first() == nullptr && this->second() == nullptr && this->third() == nullptr){
        return true;
    }else {
        return false;
    }

}
