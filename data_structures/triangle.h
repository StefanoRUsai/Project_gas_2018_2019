#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cg3/geometry/2d/point2d.h>


class Triangle{


    private:
        cg3::Point2Dd* vertexOne;
        cg3::Point2Dd* vertexTwo;
        cg3::Point2Dd* vertexThree;

        Triangle* adjacentOne = nullptr;
        Triangle* adjacentTwo = nullptr;
        Triangle* adjacentThree = nullptr;
        //Dag* node = nullptr;  // link al nodo di appartenenza nel dag per il triancolo


    public:
        Triangle();
        Triangle(cg3::Point2Dd* vertexOne,
                 cg3::Point2Dd* vertexTwo,
                 cg3::Point2Dd* vertexThree);
        ~Triangle(); //distruttore da rivedere?

        /**
         * @brief Getter
         * @return
         */
        cg3::Point2Dd* getVertexOne() const;
        cg3::Point2Dd* getVertexTwo() const;
        cg3::Point2Dd* getVertexThree() const;
        Triangle* getAdjacentOne() const;
        Triangle* getAdjacentTwo() const;
        Triangle* getAdjacentThree() const;

        /**
         * @brief Setter
         * @return
         */
        void setVertexOne(cg3::Point2Dd* vertexOne);
        void setVertexTwo(cg3::Point2Dd* vertexTwoo);
        void setVertexThree(cg3::Point2Dd* vertexThree);

        void setAdjacentOne(Triangle* adjacentOne);
        void setAdjacentTwo(Triangle* adjacentTwoo);
        void setAdjacentThree(Triangle* adjacentThree);
        bool controlPoint (const cg3::Point2Dd& point);
        bool pointIsVertex(const cg3::Point2Dd& p);
};

#endif // TRIANGLE_H
