#include "pointcollectiondrawer.h"

#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>

const cg3::Point2Dd distance(1e+6, 0);
const cg3::Point2Dd negDistance(-1e+6, 0);

template<class Container>
/**
 * @brief PointCollectionDrawer<Container>::PointCollectionDrawer
 */
PointCollectionDrawer<Container>::PointCollectionDrawer() :
    containerPointer(nullptr),
    color(QColor(255,0,0))
{

}

template<class Container>
/**
 * @brief PointCollectionDrawer<Container>::setPoints
 * @param value
 */
void PointCollectionDrawer<Container>::setPoints(Container* value)
{
    this->containerPointer = value;
}



template<class Container>
/**
 * @brief PointCollectionDrawer<Container>::setColor
 * @param color
 */
void PointCollectionDrawer<Container>::setColor(const QColor& color)
{
    this->color = color;
}


template<class Container>
/**
 * @brief PointCollectionDrawer<Container>::draw
 */
void PointCollectionDrawer<Container>::draw() const {
    for (const cg3::Point2Dd& p : *this->containerPointer) {
        cg3::viewer::drawPoint2D(p, color, 3);
    }
}

/**
 * @brief Get the center of the collection of points
 * @return Center of the scene
 */
template<class Container>
/**
 * @brief PointCollectionDrawer<Container>::sceneCenter
 * @return
 */
cg3::Pointd PointCollectionDrawer<Container>::sceneCenter() const {

    return cg3::Pointd(0, 0);

}

template<class Container>
/**
 * @brief PointCollectionDrawer<Container>::sceneRadius
 * @return
 */
double PointCollectionDrawer<Container>::sceneRadius() const {

    return (negDistance.dist(distance))/2;
}


