#include "drawabletriangulation.h"
#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>
#include <cg3/viewer/interfaces/drawable_object.h>

using namespace cg3;

DrawableTriangulation::DrawableTriangulation() :color(QColor(0,0,255))
{

}


/**
 * @brief Set color of the edges of the convex hull
 * @param color Color of the edges
 */
void DrawableTriangulation::setColor(const QColor& color)
{
    this->color = color;
}


//DrawableTriangulation::DrawableTriangulation(){}

/**
 * @brief Drawable_triangulation::draw
 * This method draw the triangle inside the canvas.
 * If activeBoundingTriangle is true print all points and edges, otherwise only the point inside the bounding triangle an the edges that
 * not lie in one of three verticies of the bounding triangle
 */

void DrawableTriangulation::draw() const{
    // Edges

    for(Triangle* t: triangles){
        cg3::viewer::drawLine2D( t->v1(), t->v2(),  color, 2);
        cg3::viewer::drawLine2D( t->v2(), t->v3(), color, 2);
        cg3::viewer::drawLine2D( t->v3(), t->v1(), color, 2);

        std::cout<<"separatore"<<std::endl;
        t->printTriangle();

    }

}

Pointd DrawableTriangulation::sceneCenter() const {
   return Pointd(0, 0);
}

double DrawableTriangulation::sceneRadius() const {
    return -1;
}

void DrawableTriangulation::setActiveBoundingTriangle(bool b){
    this->activeBoundingTriangle = b;
}


void DrawableTriangulation::eraseTriangles(){
    this->triangles.clear();
}

void DrawableTriangulation::setTriangles(const std::vector<delaunay::Triangle* >& t){
    this->eraseTriangles();
    this->triangles = t;
}


