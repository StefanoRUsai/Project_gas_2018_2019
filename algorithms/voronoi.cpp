#include "voronoi.h"

/**
 * @brief circumcircle
 * @param t is the triangle
 * @link https://en.wikipedia.org/wiki/Circumscribed_circle#Circumcenter_coordinates
 */
Point2Dd voronoi::circumcircle(Triangle* t){

    double D = 2 * ( t->v1().x() * (t->v2().y() - t->v3().y()) + t->v2().x() * (t->v3().y() - t->v1().y()) + t->v3().x() * (t->v1().y() - t->v2().y()));

    double x = (1 / D) * ( (pow(t->v1().x(),2) + pow(t->v1().y(),2)) * (t->v2().y() - t->v3().y()) +  (pow(t->v2().x(),2) +
                            pow(t->v2().y(),2)) * (t->v3().y() - t->v1().y()) +  (pow(t->v3().x(),2) + pow(t->v3().y(),2)) * (t->v1().y() - t->v2().y()));

    double y = (1 / D) * ( (pow(t->v1().x(),2) + pow(t->v1().y(),2)) * (t->v3().x() - t->v2().x()) +  (pow(t->v2().x(),2) +
                            pow(t->v2().y(),2)) * (t->v1().x() - t->v3().x()) +  (pow(t->v3().x(),2) + pow(t->v3().y(),2)) * (t->v2().x() - t->v1().x()));

    return Point2Dd(x, y);;

}
