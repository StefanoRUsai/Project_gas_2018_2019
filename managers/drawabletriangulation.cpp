#include "drawabletriangulation.h"
#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>
#include <cg3/viewer/interfaces/drawable_object.h>

using namespace cg3;

const cg3::Point2Dd BT_P1(1e+10, 0);
const cg3::Point2Dd BT_P2(0, 1e+10);
const cg3::Point2Dd BT_P3(-1e+10, -1e+10);



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
 * @brief DrawableTriangulation::draw
 * This method draw the triangle inside the canvas.
 * If activeBoundingTriangle is true print all points and edges
 */

void DrawableTriangulation::draw() const{
    // Edges

    for(Triangle* t: triangles){

        if(this->boundingTriangle){

            if(t->isLegal()){
                    cg3::viewer::drawLine2D( t->v1(), t->v2(),  color, 1);
                    cg3::viewer::drawLine2D( t->v2(), t->v3(), color, 1);
                    cg3::viewer::drawLine2D( t->v3(), t->v1(), color, 1 );
            }
        }else{
            if(t->isLegal()){
                if(printPoint(t->v1())&& printPoint(t->v2()))
                    cg3::viewer::drawLine2D( t->v1(), t->v2(),  color, 1);
                if(printPoint(t->v2())&& printPoint(t->v3()))
                    cg3::viewer::drawLine2D( t->v2(), t->v3(), color, 1);
                if(printPoint(t->v3())&& printPoint(t->v1()))
                    cg3::viewer::drawLine2D( t->v3(), t->v1(), color, 1 );
            }

        }


    }

}


/**
 * @brief DrawableTriangulation::setBoundingTriangleActive
 * @param b, simple boolean value
 */



bool DrawableTriangulation::printPoint(const Point2Dd& p) const{
    return ( p != BT_P1 && p != BT_P2 && p != BT_P3); //
}

Pointd DrawableTriangulation::sceneCenter() const {
    cg3::Pointd center(0,0,0);
    for (const cg3::Point2Dd& p : *this->points) {
        center.x() += p.x();
        center.y() += p.y();
    }
    center /= (this->points)->size();

    return center;

}

double DrawableTriangulation::sceneRadius() const {
    cg3::Pointd center = sceneCenter();

    double maxDistance = 0;
    for (const cg3::Point2Dd& p : *this->points) {
        cg3::Point2Dd center2D(center.x(), center.y());
        double dist = p.dist(center2D);

        maxDistance = std::max(dist, maxDistance);
    }

    return maxDistance;
}

void DrawableTriangulation::setActiveBoundingTriangle(bool b){
    this->boundingTriangle = b;
}


void DrawableTriangulation::eraseTriangles(){
    this->triangles.clear();
}

void DrawableTriangulation::setTriangles(std::vector<cg3::Point2Dd> *p, const std::vector<delaunay::Triangle* >& t){
    this->points=p;
    this->eraseTriangles();
    this->triangles = t;
}


