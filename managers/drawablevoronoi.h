#ifndef DRAWABLEVORONOI_H
#define DRAWABLEVORONOI_H

#include <cg3/viewer/interfaces/drawable_object.h>
#include <cg3/geometry/2d/point2d.h>
#include <data_structures/triangulation.h>

/**
 * @brief Class for representing a drawable voronoi diagrams
 */
class DrawableVoronoi: public cg3::DrawableObject{
public:
    DrawableVoronoi();


    cg3::Pointd sceneCenter() const;
    double sceneRadius() const;


    void draw() const;
    void eraseTriangles();
    void setColor(const QColor &color);
    void setTriangles(const std::vector<delaunay::Triangle *> &triangles);
protected:
    QColor color;
    std::vector<delaunay::Triangle* > _triangles;
    std::vector<cg3::Point2Dd> *points = nullptr;


};

#endif // DRAWABLEVORONOI_H
