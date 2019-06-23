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

/**
 * @brief DrawableVoronoi::draw
 * @details draws the diagram of voronoi
 */
void DrawableVoronoi::draw() const{
        for(Triangle* t: _triangles){
            if(t->isLegal()){

                viewer::drawPoint2D(circumcircle(t), QColor(0,18,12), 2);

                if(t->e1() != nullptr)
                viewer::drawLine2D(circumcircle(t), circumcircle(t->e1()), color, 1);
                if(t->e2() != nullptr)
                viewer::drawLine2D(circumcircle(t), circumcircle(t->e2()), color, 1);
                if(t->e3() != nullptr)
                viewer::drawLine2D(circumcircle(t), circumcircle(t->e3()), color, 1);

             }
        }
}



/**
 * @brief DrawableVoronoi::setColor
 * @param color
 */
void DrawableVoronoi::setColor(const QColor& color)
{
    this->color = color;
}


/**
 * @brief DrawableVoronoi::setTriangles
 * @param triangles
 */
void DrawableVoronoi::setTriangles(const std::vector<delaunay::Triangle* >& triangles){
   _triangles = triangles;
}
/**
 * @brief DrawableVoronoi::eraseTriangles
 */
void DrawableVoronoi::eraseTriangles(){
    _triangles.clear();
}
/**
 * @brief DrawableVoronoi::sceneCenter
 * @return
 */
Pointd DrawableVoronoi::sceneCenter() const {
//    cg3::Pointd center(0,0,0);
//    for (const cg3::Point2Dd& p : *this->points) {
//        center.x() += p.x();
//        center.y() += p.y();
//    }
//    center /= (this->points)->size();

//    return center;

    return Pointd(0, 0);
}
/**
 * @brief DrawableVoronoi::sceneRadius
 * @return
 */
double DrawableVoronoi::sceneRadius() const {
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





