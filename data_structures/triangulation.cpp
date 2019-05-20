#include "node.h"
#include "triangulation.h"
using namespace delaunay;
Triangulation::Triangulation(){}


std::vector<delaunay::Triangle*> Triangulation::getDrawTriangles(){
    return drawTriangles;
}

void Triangulation::addDrawTriangles(delaunay::Triangle* t){
    drawTriangles.push_back(t);
}
