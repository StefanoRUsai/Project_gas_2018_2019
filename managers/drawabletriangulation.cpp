#include "drawabletriangulation.h"
#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>
#include <cg3/viewer/interfaces/drawable_object.h>

using namespace cg3;

// points of the bounding triangle
const cg3::Point2Dd BT_P1(1e+10, 0);
const cg3::Point2Dd BT_P2(0, 1e+10);
const cg3::Point2Dd BT_P3(-1e+10, -1e+10);



DrawableTriangulation::DrawableTriangulation() :color(QColor(0,0,255))
{

}


/**
 * @brief DrawableTriangulation::setColor
 * @details setColor of the edges of the delaunay triangualation
 * @param color
 */
void DrawableTriangulation::setColor(const QColor& color)
{
    this->color = color;
}


/**
 * @brief DrawableTriangulation::draw
 * @details the method serves to draw the triangulation, if the bounding triangle is active it will draw everything
 */
void DrawableTriangulation::draw() const{


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
 * @brief DrawableTriangulation::printPoint
 * @details points of the bounding triangle that should not be drawn
 * @param p
 * @return
 */
bool DrawableTriangulation::printPoint(const Point2Dd& p) const{
    return ( p != BT_P1 && p != BT_P2 && p != BT_P3); //
}

Pointd DrawableTriangulation::sceneCenter() const {
//    cg3::Pointd center(0,0,0);
//    for (const cg3::Point2Dd& p : *this->points) {
//        center.x() += p.x();
//        center.y() += p.y();
//    }
//    center /= (this->points)->size();

//    return center;

    return Pointd(0, 0);

}

double DrawableTriangulation::sceneRadius() const {
//    cg3::Pointd center = sceneCenter();

//    double maxDistance = 0;
//    for (const cg3::Point2Dd& p : *this->points) {
//        cg3::Point2Dd center2D(center.x(), center.y());
//        double dist = p.dist(center2D);

//        maxDistance = std::max(dist, maxDistance);
//    }

//    return maxDistance;

    return -1;
}

/**
 * @brief DrawableTriangulation::setActiveBoundingTriangle
 * @param b
 */
void DrawableTriangulation::setActiveBoundingTriangle(bool b){
    this->boundingTriangle = b;
}

/**
 * @brief DrawableTriangulation::eraseTriangles
 */
void DrawableTriangulation::eraseTriangles(){
    this->triangles.clear();
}

/**
 * @brief DrawableTriangulation::setTriangles
 * @details sets the initialization of the class that draws the triangulation
 * @param t
 */
void DrawableTriangulation::setTriangles( const std::vector<delaunay::Triangle* >& t){

    this->eraseTriangles();
    this->triangles = t;
}


