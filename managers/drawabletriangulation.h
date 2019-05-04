#ifndef DRAWABLETRIANGULATION_H
#define DRAWABLETRIANGULATION_H


#include <cg3/viewer/interfaces/drawable_object.h>
#include <cg3/geometry/2d/point2d.h>


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

private:

    QColor color; //Color of the edges
};

#endif // DRAWABLETRIANGULATION_H
