#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cg3/geometry/2d/point2d.h>
using namespace cg3;

class Dag;
class Triangle{


    private:
        cg3::Point2Dd vertexOne;
        cg3::Point2Dd vertexTwo;
        cg3::Point2Dd vertexThree;
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
        void setVertexOne(cg3::Point2Dd* vertexOne);
        void setVertexTwo(cg3::Point2Dd* vertexTwoo);
        void setVertexThree(cg3::Point2Dd* vertexThree);
        void setNode(Dag* node);
        bool controlPoint (const cg3::Point2Dd& point);
        bool pointIsVertex(const cg3::Point2Dd& p);
};

#endif // TRIANGLE_H
