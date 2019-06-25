#ifndef POINTCOLLECTIONDRAWER_H
#define POINTCOLLECTIONDRAWER_H

#include <cg3/viewer/drawable_objects/drawable_objects.h>
#include <cg3/geometry/2d/point2d.h>


/**
 * @brief Class for representing a point
 */
template<class Container>
class PointCollectionDrawer : public cg3::DrawableObject
{
public:
    PointCollectionDrawer();

    void setPoints(Container* value);
    void setColor(const QColor &value);

    /* --- DrawableObject interface --- */

    void draw() const;
    cg3::Pointd sceneCenter() const;
    double sceneRadius() const;


private:
    Container* containerPointer;
    QColor color; // Color of point

};

#include "pointcollectiondrawer.tpp"
#endif // POINTCOLLECTIONDRAWER_H
