#include "delaunay.h"
#include <managers/delaunaymanager.h>
#include <utils/delaunay_checker.h>

using namespace delaunay;
/**
 * @brief triangulation
 * @param BT_P1 point the bounding triangle
 * @param BT_P2 point the bounding triangle
 * @param BT_P3 point the bounding triangle
 */
Triangulation* delaunay::triangulation(const Point2Dd& BT_P1, const Point2Dd& BT_P2, const Point2Dd& BT_P3){
    Triangle* t = new Triangle(BT_P1, BT_P2, BT_P3);
    Node *node = new Node(t);
    Triangulation* tri = new Triangulation(t, node);

    return tri;
}

/**
 * @brief triangulation
 * @param BT_P1 point the bounding triangle
 * @param BT_P2 point the bounding triangle
 * @param BT_P3 point the bounding triangle
 * @param points are the initial set for triangulation,
   The algorithm follows the specification of the permutation on the set of start points.
 */
Triangulation* delaunay::triangulation(const std::vector<cg3::Point2Dd>& points,
                             const Point2Dd& BT_P1, const Point2Dd& BT_P2, const Point2Dd& BT_P3){
    std::vector<cg3::Point2Dd> newPoints = points;
    Triangle* t = new Triangle(BT_P1, BT_P2, BT_P3);
    Node *node = new Node(t);

    Triangulation* tri = new Triangulation(t, node);

    std::srand ( unsigned ( std::time(nullptr) ) );
    std::random_shuffle ( newPoints.begin(), newPoints.end() );

    tri->addList(points);

    return tri;
}





