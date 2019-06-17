#ifndef DRAWABLEVORONOI_H
#define DRAWABLEVORONOI_H

#include <cg3/viewer/interfaces/drawable_object.h>
#include <cg3/geometry/2d/point2d.h>
#include <data_structures/triangulation.h>

class DrawableVoronoi: public cg3::DrawableObject{
public:
    DrawableVoronoi();


    cg3::Pointd sceneCenter() const;
    double sceneRadius() const;


    void draw() const;
    void setTriangles(const std::vector<delaunay::Triangle* >& t);
    void eraseTriangles();
    void setColor(const QColor &color);
protected:
    QColor color;
    std::vector<delaunay::Triangle* > _triangles;
};

#endif // DRAWABLEVORONOI_H
