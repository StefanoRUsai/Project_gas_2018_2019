#ifndef DRAWABLETRIANGULATION_H
#define DRAWABLETRIANGULATION_H


#include <cg3/viewer/interfaces/drawable_object.h>
#include <cg3/geometry/2d/point2d.h>
#include <data_structures/triangulation.h>

using namespace delaunay;
/**
 * @brief Class for representing a drawable triangulation
 */
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
    void eraseTriangles();
    bool printPoint(const Point2Dd &p) const;
    void setTriangles(std::vector<cg3::Point2Dd> *p, const std::vector<delaunay::Triangle *> &t);
    void setTriangles(const std::vector<delaunay::Triangle *> &t);
private:

    QColor color; //Color of the edges
    bool boundingTriangle=false; // flag
    std::vector<delaunay::Triangle* > triangles; // vector of triangles to be printed






};

#endif // DRAWABLETRIANGULATION_H
