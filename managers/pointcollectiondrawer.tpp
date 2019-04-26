#include "pointcollectiondrawer.h"

#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>

/**
 * @brief Default constructor
 */
template<class Container>
PointCollectionDrawer<Container>::PointCollectionDrawer() :
    containerPointer(nullptr),
    color(QColor(255,0,0))
{

}

/**
 * @brief Setter for the container of the points
 * @param containerPointer Pointer to the container to draw
 */
template<class Container>
void PointCollectionDrawer<Container>::setPoints(Container* value)
{
    this->containerPointer = value;
}

/**
 * @brief Set point color
 * @param color Color
 */
template<class Container>
void PointCollectionDrawer<Container>::setColor(const QColor& color)
{
    this->color = color;
}


/**
 * @brief Method for drawing a collection of points
 */
template<class Container>
void PointCollectionDrawer<Container>::draw() const {
    for (const cg3::Point2Dd& p : *this->containerPointer) {
        cg3::viewer::drawPoint2D(p, color, 5);
    }
}

/**
 * @brief Get the center of the collection of points
 * @return Center of the scene
 */
template<class Container>
cg3::Pointd PointCollectionDrawer<Container>::sceneCenter() const {
    cg3::Pointd center(0,0,0);
    for (const cg3::Point2Dd& p : *this->containerPointer) {
        center.x() += p.x();
        center.y() += p.y();
    }
    center /= (*this->containerPointer).size();

    return center;
}

/**
 * @brief Get the radius of the scene containing the collection of points
 * @return Radius of the scene
 */
template<class Container>
double PointCollectionDrawer<Container>::sceneRadius() const {
    cg3::Pointd center = sceneCenter();

    double maxDistance = 0;
    for (const cg3::Point2Dd& p : *this->containerPointer) {
        cg3::Point2Dd center2D(center.x(), center.y());
        double dist = p.dist(center2D);

        maxDistance = std::max(dist, maxDistance);
    }

    return maxDistance;
}
