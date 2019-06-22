#ifndef DRAWABLETRIANGULATION_H
#define DRAWABLETRIANGULATION_H


#include <cg3/viewer/interfaces/drawable_object.h>
#include <cg3/geometry/2d/point2d.h>
#include <data_structures/triangulation.h>

using namespace delaunay;

class DrawableTriangulation: public cg3::DrawableObject {
public:

    /* --- Constructors --- */

    DrawableTriangulation();
    DrawableTriangulation(const std::list<cg3::Point2Dd>& points);

    /* --- Methods --- */

    void setColor(const QColor &value);

    /* --- DrawableObject interface --- */

    void draw() const;
    cg3::Pointd sceneCenter() const;
    double sceneRadius() const;

    void setActiveBoundingTriangle(bool b);
    void setTriangles(const std::vector<delaunay::Triangle* >& t);
    void eraseTriangles();
    bool printPoint(const Point2Dd &p) const;
private:

    QColor color; //Color of the edges
    bool boundingTriangle=false;
    std::vector<delaunay::Triangle* > triangles;




};

#endif // DRAWABLETRIANGULATION_H
