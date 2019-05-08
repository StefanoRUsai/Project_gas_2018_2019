#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cg3/geometry/2d/point2d.h>
using namespace cg3;
namespace  delaunay{
class Dag;
class Triangle{


    protected:
        Point2Dd _vertexOne;
        Point2Dd _vertexTwo;
        Point2Dd _vertexThree;
        Dag* node = nullptr;  // link al nodo di appartenenza nel dag per il triancolo


    public:
        Triangle();
        Triangle(const Point2Dd& vertexOne,
                 const Point2Dd& vertexTwo,
                 const Point2Dd& vertexThree);
        ~Triangle(); //distruttore da rivedere?

        /**
         * @brief Getter
         * @return
         */
        cg3::Point2Dd getVertexOne() const;
        cg3::Point2Dd getVertexTwo() const;
        cg3::Point2Dd getVertexThree() const;

        /**
         * @brief Setter
         * @return
         */
        void setNode(Dag* node);

        /**
         * @brief controlPoint
         * @param point
         * @return
         */

        bool controlPoint (const cg3::Point2Dd& point);
        /**
         * @brief pointIsVertex
         * @param p
         * @return
         */
        bool pointIsVertex(const cg3::Point2Dd& p);
        void printTriamgle();
};
}
#endif // TRIANGLE_H
