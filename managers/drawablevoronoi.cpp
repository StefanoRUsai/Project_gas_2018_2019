#include "drawablevoronoi.h"
#include "drawablevoronoi.h"
#include "drawablevoronoi.h"
#include <algorithms/voronoi.h>
#include <data_structures/triangulation.h>
#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>
#include <cg3/viewer/interfaces/drawable_object.h>

using namespace cg3;
using namespace delaunay;
using namespace voronoi;

DrawableVoronoi::DrawableVoronoi():color(QColor(255,0,0)){}

void DrawableVoronoi::draw() const{
        for(Triangle* t: _triangles){
            if(t->isLegal()){

                viewer::drawPoint2D(circumcircle(t), QColor(0,255,0), 5);

                if(t->e1() != nullptr)
                viewer::drawLine2D(circumcircle(t), circumcircle(t->e1()), color, 3);
                if(t->e2() != nullptr)
                viewer::drawLine2D(circumcircle(t), circumcircle(t->e2()), color, 3);
                if(t->e3() != nullptr)
                viewer::drawLine2D(circumcircle(t), circumcircle(t->e3()), color, 3);

             }
        }
}



/**
 * @brief Set color of the edges of the convex hull
 * @param color Color of the edges
 */
void DrawableVoronoi::setColor(const QColor& color)
{
    this->color = color;
}



void DrawableVoronoi::setTriangles(const std::vector<delaunay::Triangle* >& triangles){
   _triangles = triangles;
}

void DrawableVoronoi::eraseTriangles(){
    _triangles.clear();
}

Pointd DrawableVoronoi::sceneCenter() const {
   return Pointd(0, 0);
}

double DrawableVoronoi::sceneRadius() const {
    return -1;
}





