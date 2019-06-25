#include "node.h"
#include "triangulation.h"
#include "triangle.h"

#include <utils/delaunay_checker.h>
#include <cg3/core/cg3/geometry/2d/utils2d.h>

using namespace delaunay;
Triangulation::Triangulation()= default;

/**
 * @brief Triangulation::~Triangulation
 */
Triangulation::~Triangulation(){
    for(auto t: drawTriangles){
        delete t;
    }

    for(auto n: _dag.nodes()){
        delete n;
    }
}



/**
 * @brief Triangulation::Triangulation
 * @details manufacturer of the triangulation with the passage of the
   initial triangle starting from the vertices and initializing the dag
 * @param BT_P1
 * @param BT_P2
 * @param BT_P3
 */
Triangulation::Triangulation(const Point2Dd& BT_P1, const Point2Dd& BT_P2, const Point2Dd& BT_P3){

    delaunay::Triangle start(BT_P3,BT_P1,BT_P2);
    Node node(&start);
    addDrawTriangles(&start);
    this->_dag.setNodes(&node);

}
/**
 * @brief Triangulation::Triangulation
 * @details manufacturer of the triangulation with the passage of the initial triangle and the first knot on the dag
 * @param t
 * @param node
 */
Triangulation::Triangulation(Triangle* t, Node* node){

    addDrawTriangles(t);
    this->_dag.setNodes(node);
}

/**
 * @brief Triangulation::eraseTriangulation
 */
void Triangulation::eraseTriangulation(){

    drawTriangles.erase(drawTriangles.begin(), drawTriangles.end());
    _dag.erase();

}



/**
 * @brief Triangulation::addList
 * @details adds a list of points to the triangulation
 * @param points
 */
void Triangulation::addList(const std::vector<cg3::Point2Dd>& points){
    for(const Point2Dd& point: points){

        this->unionEdge(point);
    }
}

/**
 * @brief Triangulation::addPoint
 * @details adds points to the triangulation
 * @param point
 */
void Triangulation::addPoint( Point2Dd& point){

    this->unionEdge(point);
}

std::vector<delaunay::Triangle*> Triangulation::getDrawTriangles(){
    return drawTriangles;
}
/**
 * @brief Triangulation::addDrawTriangles
 * @details adds the triangles to the vector of the triangles that will then be printed
 * @param t
 */
void Triangulation::addDrawTriangles(delaunay::Triangle* t){
    drawTriangles.push_back(t);
}

/**
 * @brief Triangulation::unionEdge
 * @details joins the points to the vertices
 * @param point
 */
void Triangulation::unionEdge(const Point2Dd& point){
    delaunay::Node *node=this->_dag.navigateGraph(point);
    delaunay::Triangle *t = node->t();

    if (areCollinear(t->v1(), t->v2(), point)){
        this->subdivisionTriangleDoubleE1(point,t , node, &_dag);
    }else if (areCollinear(t->v2(), t->v3(), point)){
        this->subdivisionTriangleDoubleE2(point, t , node, &_dag);
    }else if (areCollinear(t->v3(), t->v1(), point)){
        this->subdivisionTriangleDoubleE3(point,t , node, &_dag);
    } else {
        this->subdivisionTriangle(point,t, node, &_dag);
    }




}
/**
 * @brief Triangulation::subdivisionTriangle
 * @details basic function with which the triangulation is created,
   this subdivides a triangle joining the vertices to the inserted point and setting the adjacencies of the created triangles
 * @param point
 * @param triangle
 * @param node
 * @param dag
 */
void Triangulation::subdivisionTriangle(const Point2Dd& point, Triangle* triangle, Node* node, Dag* dag){

    delaunay::Triangle* tr1 = Triangulation::createTriangle(point, triangle->v1(), triangle->v2(), node, dag);
    delaunay::Triangle* tr2 = Triangulation::createTriangle(point, triangle->v2(), triangle->v3(), node, dag);
    delaunay::Triangle* tr3 = Triangulation::createTriangle(point, triangle->v3(), triangle->v1(), node, dag);

    triangle->setIllegal();

    tr1->sete1(tr3);
    tr1->sete2(triangle->PointsAdjacent(tr1->v2(),tr1->v3()));
    if(triangle->PointsAdjacent(tr1->v2(),tr1->v3()) != nullptr)
        tr1->e2()->twoPointsEdgeAdjacentFlip(tr1->v2(),tr1->v3(), tr1);
    tr1->sete3(tr2);

    tr2->sete1(tr1);
    tr2->sete2(triangle->PointsAdjacent(tr2->v2(),tr2->v3()));
    if(triangle->PointsAdjacent(tr2->v2(),tr2->v3()) != nullptr)
        tr2->e2()->twoPointsEdgeAdjacentFlip(tr2->v2(),tr2->v3(), tr2);
    tr2->sete3(tr3);


    tr3->sete1(tr2);
    tr3->sete2(triangle->PointsAdjacent(tr3->v2(),tr3->v3()));
    if(triangle->PointsAdjacent(tr3->v2(),tr3->v3()) != nullptr)
        tr3->e2()->twoPointsEdgeAdjacentFlip(tr3->v2(),tr3->v3(), tr3);
    tr3->sete3(tr1);

    legalizeEdge(point, triangle->v1(), triangle->v2(), tr1, dag);
    legalizeEdge(point, triangle->v2(), triangle->v3(), tr2, dag);
    legalizeEdge(point, triangle->v3(), triangle->v1(), tr3, dag);

}

/**
 * @brief Triangulation::subdivisionTriangleDoubleE1
 * @details subdivision into 4 triangles starting from edge 1
    reminding us that the triangles are created in an anticlockwise direction, the construction should be as follows
 * @param point
 * @param triangle
 * @param node
 * @param dag
 */
void Triangulation::subdivisionTriangleDoubleE1(const Point2Dd& point, Triangle* triangle, Node* node, Dag* dag){

    delaunay::Triangle* tr1_1 = Triangulation::createTriangle(point, triangle->v2(), triangle->v3(), node, dag);
    delaunay::Triangle* tr1_2 = Triangulation::createTriangle(point, triangle->v3(), triangle->v1(), node, dag);

    const Point2Dd tp = triangle->e1()->thirdpoint(triangle->v1(), triangle->v2());

    delaunay::Triangle* tr2_1 = Triangulation::createTriangle(point, tp, triangle->v2(), triangle->e1()->node(), dag);
    delaunay::Triangle* tr2_2 = Triangulation::createTriangle(point, triangle->v1(), tp, triangle->e1()->node(), dag);

    triangle->setIllegal();
    triangle->e1()->setIllegal();


    tr2_1->sete1(tr2_2);
    tr2_1->sete2(triangle->e1()->searchAdjacentTriangle(tp, triangle->v2()));
    if (triangle->e1()->searchAdjacentTriangle(tp, triangle->v2()) != nullptr)
        tr2_1->e2()->twoPointsEdgeAdjacentFlip(tp, triangle->v2(), tr2_1);
    tr2_1->sete3(tr1_1);

    tr2_2->sete1(tr1_2);
    tr2_2->sete2(triangle->e1()->searchAdjacentTriangle(triangle->v1(), tp));
    if (triangle->e1()->searchAdjacentTriangle(triangle->v1(), tp) != nullptr)
        tr2_2->e2()->twoPointsEdgeAdjacentFlip(triangle->v1(), tp, tr2_2);
    tr2_2->sete3(tr2_1);

    tr1_1->sete1(tr2_1);
    if(triangle->e2()!=nullptr){
        tr1_1->sete2(triangle->e2());
        triangle->e2()->twoPointsEdgeAdjacentFlip(tr1_1->v2(), tr1_1->v3(), tr1_1);
    }
    tr1_1->sete3(tr1_2);

    tr1_2->sete1(tr1_1);
    if(triangle->e3()!=nullptr){
        tr1_2->sete2(triangle->e3());
        triangle->e3()->twoPointsEdgeAdjacentFlip(tr1_2->v2(), tr1_2->v3(), tr1_2);
    }
    tr1_2->sete3(tr2_2);


    legalizeEdge(point, triangle->v1(), triangle->v2(), tr1_1, dag);
    legalizeEdge(point, triangle->v3(), triangle->v1(), tr1_2, dag);
    legalizeEdge(point, triangle->v2(), tp, tr2_1, dag);
    legalizeEdge(point, tp, triangle->v3(), tr2_2, dag);
}

/**
 * @brief Triangulation::subdivisionTriangleDoubleE2
 * @details subdivision into 4 triangles starting from edge 2
    reminding us that the triangles are created in an anticlockwise direction, the construction should be as follows
 * @param point
 * @param triangle
 * @param node
 * @param dag
 */
void Triangulation::subdivisionTriangleDoubleE2(const Point2Dd& point, Triangle* triangle, Node* node, Dag* dag){

    delaunay::Triangle* tr1_1 = Triangulation::createTriangle(point, triangle->v1(), triangle->v2(), node, dag);
    delaunay::Triangle* tr1_2 = Triangulation::createTriangle(point, triangle->v3(), triangle->v1(), node, dag);

    const Point2Dd tp = triangle->e2()->thirdpoint(triangle->v2(), triangle->v3());



    delaunay::Triangle* tr2_1 = Triangulation::createTriangle(point, triangle->v2(), tp, triangle->e2()->node(), dag);
    delaunay::Triangle* tr2_2 = Triangulation::createTriangle(point, tp, triangle->v3(),  triangle->e2()->node(), dag);


    triangle->setIllegal();
    triangle->e2()->setIllegal();

    tr2_1->sete1(tr1_1);
    tr2_1->sete2(triangle->e2()->searchAdjacentTriangle(triangle->v2(), tp));
    if (triangle->e2()->searchAdjacentTriangle(triangle->v2(), tp) != nullptr)
        tr2_1->e2()->twoPointsEdgeAdjacentFlip(triangle->v2(), tp, tr2_1);
    tr2_1->sete3(tr2_2);

    tr2_2->sete1(tr2_1);
    tr2_2->sete2(triangle->e2()->searchAdjacentTriangle(tp, triangle->v3()));
    if (triangle->e2()->searchAdjacentTriangle(tp, triangle->v3()) != nullptr)
        tr2_2->e2()->twoPointsEdgeAdjacentFlip(tp, triangle->v3(), tr2_2);
    tr2_2->sete3(tr1_2);

    tr1_1->sete1(tr1_2);
    if(triangle->e2()!=nullptr){
        tr1_1->sete2(triangle->e2());
        triangle->e2()->twoPointsEdgeAdjacentFlip(tr1_1->v2(), tr1_1->v3(), tr1_1);
    }
    tr1_1->sete3(tr2_1);

    tr1_2->sete1(tr2_2);
    if(triangle->e3()!=nullptr){
        tr1_2->sete2(triangle->e3());
        triangle->e3()->twoPointsEdgeAdjacentFlip(tr1_2->v2(), tr1_2->v3(), tr1_2);
    }
    tr1_2->sete3(tr1_1);



    legalizeEdge(point, triangle->v1(), triangle->v2(), tr1_1, dag);
    legalizeEdge(point, triangle->v3(), triangle->v1(), tr1_2, dag);
    legalizeEdge(point, triangle->v2(), tp, tr2_1, dag);
    legalizeEdge(point, tp, triangle->v3(), tr2_2, dag);

}

/**
 * @brief Triangulation::subdivisionTriangleDoubleE3
 * @details subdivision into 4 triangles starting from edge 3
    reminding us that the triangles are created in an anticlockwise direction, the construction should be as follows
 * @param point
 * @param triangle
 * @param node
 * @param dag
 */
void Triangulation::subdivisionTriangleDoubleE3(const Point2Dd& point, Triangle* triangle, Node* node, Dag* dag){


    delaunay::Triangle* tr1_1 = Triangulation::createTriangle(point, triangle->v2(), triangle->v3(), node, dag);
    delaunay::Triangle* tr1_2 = Triangulation::createTriangle(point, triangle->v1(), triangle->v2(), node, dag);

    const Point2Dd tp = triangle->e3()->thirdpoint(triangle->v3(), triangle->v1());

    delaunay::Triangle* tr2_1 = Triangulation::createTriangle(point, triangle->v3(), tp, triangle->e3()->node(), dag);
    delaunay::Triangle* tr2_2 = Triangulation::createTriangle(point, tp, triangle->v1(),  triangle->e3()->node(), dag);

    triangle->setIllegal();
    triangle->e3()->setIllegal();

    tr2_1->sete1(tr1_1);
    tr2_1->sete2(triangle->e3()->searchAdjacentTriangle(triangle->v3(), tp));
    if (triangle->e3()->searchAdjacentTriangle(triangle->v3(), tp) != nullptr)
        tr2_1->e2()->twoPointsEdgeAdjacentFlip(triangle->v3(), tp, tr2_1);
    tr2_1->sete3(tr2_2);

    tr2_2->sete1(tr2_1);
    tr2_2->sete2(triangle->e2()->searchAdjacentTriangle(tp, triangle->v1()));
    if (triangle->e2()->searchAdjacentTriangle(tp, triangle->v1()) != nullptr)
        tr2_2->e2()->twoPointsEdgeAdjacentFlip(tp, triangle->v1(), tr2_2);
    tr2_2->sete3(tr1_2);

    tr1_1->sete1(tr1_2);
    if(triangle->e2()!=nullptr){
        tr1_1->sete2(triangle->e2());
        triangle->e2()->twoPointsEdgeAdjacentFlip(tr1_1->v2(), tr1_1->v3(), tr1_1);
    }
    tr1_1->sete3(tr2_1);

    tr1_2->sete1(tr2_2);
    if(triangle->e1()!=nullptr){
        tr1_2->sete2(triangle->e1());
        triangle->e1()->twoPointsEdgeAdjacentFlip(tr1_2->v2(), tr1_2->v3(), tr1_1);
    }
    tr1_2->sete3(tr1_1);


    legalizeEdge(point, triangle->v2(), triangle->v3(), tr1_1, dag);
    legalizeEdge(point, triangle->v2(), triangle->v1(), tr1_2, dag);
    legalizeEdge(point, triangle->v3(), tp, tr2_1, dag);
    legalizeEdge(point, tp, triangle->v1(), tr2_2, dag);


}


/**
 * @brief Triangulation::createTriangle
 * @details creation of the triangle, also setting the node of belonging and adding it to the dag
 * @param one
 * @param two
 * @param three
 * @param node
 * @param dag
 * @return triangle
 */
Triangle* Triangulation::createTriangle(const Point2Dd& one,const Point2Dd& two, const Point2Dd& three, Node *node, Dag *dag){
    Triangle* t = new Triangle(one, two, three);
    Node* n = new Node();
    n->setTriangle(t);
    t->setNode(n);
    dag->setNodes(n);
    node->add(n);
    return t;
}
/**
 * @brief Triangulation::createTriangle
 * @details is executed when the flip occurs and the triangle needs to be derived from 2 parent nodes
 * @param one
 * @param two
 * @param three
 * @param node1
 * @param node2
 * @param dag
 * @return triangle
 */
Triangle* Triangulation::createTriangle(const Point2Dd& one,const Point2Dd& two, const Point2Dd& three, Node *node1, Node *node2, Dag *dag){
    Triangle* t = new Triangle(one, two, three);
    Node* n = new Node();
    n->setTriangle(t);
    t->setNode(n);
    dag->setNodes(n);
    node1->add(n);
    node2->add(n);
    return t;
}

/**
 * @brief Triangulation::legalizeEdge
 * @details control of triangles according to delaunay's algorithm using the verification function provided
 * @param pr
 * @param pi
 * @param pj
 * @param t
 * @param dag
 */

void Triangulation::legalizeEdge(const Point2Dd& pr, const Point2Dd& pi, const Point2Dd& pj, Triangle* t, Dag* dag){

    Triangle* adjacent = t->PointsAdjacent(pi, pj);


    if(adjacent != nullptr){
        if(DelaunayTriangulation::Checker::isPointLyingInCircle(adjacent->v1(), adjacent->v2(), adjacent->v3(), pr, false)){
            edgeFlip(pr, pi, pj, t, adjacent, dag);

        }else{
            this->addDrawTriangles(t);
        }
    }else{
        this->addDrawTriangles(t);
    }

}

/**
 * @brief Triangulation::edgeFlip
 * @details function to perform flip according to delaunay algorithm
 * @param pr
 * @param pi
 * @param pj
 * @param tr1
 * @param tr2
 * @param dag
 */
void Triangulation::edgeFlip(const Point2Dd& pr, const Point2Dd& pi, const Point2Dd& pj, Triangle* tr1, Triangle* tr2, Dag* dag ){

    tr1->setIllegal();
    tr2->setIllegal();

    Triangle* ntr1 = nullptr;
    Triangle* ntr2 = nullptr;

    const Point2Dd pk = tr2->thirdpoint(pi, pj);


    ntr1 = createTriangle(pr, pi, pk, tr1->node(), tr2->node(), dag );
    ntr2 = createTriangle(pr, pk, pj, tr1->node(), tr2->node(), dag );

    ntr1->sete3(ntr2); //e3 pk -> pr
    ntr2->sete1(ntr1); // e1 pr -> pk

    if(tr1->PointsAdjacent(pr,pi) != nullptr && tr1->PointsAdjacent(pr,pi)->isLegal() ){
        ntr1->sete1(tr1->PointsAdjacent(pr,pi)); //e1 pr -> pi
        ntr1->e1()->twoPointsEdgeAdjacentFlip(pr,pi,ntr1);//triangolo ed edge opposto
    }

    if(tr2->PointsAdjacent(pi,pk) != nullptr && tr2->PointsAdjacent(pi,pk)->isLegal()){
        ntr1->sete2(tr2->PointsAdjacent(pi,pk)); //e2 pi -> pk
        ntr1->e2()->twoPointsEdgeAdjacentFlip(pi,pk,ntr1);
    }

    if(tr2->PointsAdjacent(pk,pj) != nullptr && tr2->PointsAdjacent(pk,pj)->isLegal()){
        ntr2->sete2(tr2->PointsAdjacent(pk,pj)); // e2 pk -> pj
        ntr2->e2()->twoPointsEdgeAdjacentFlip(pk,pj,ntr2);
    }

    if(tr1->PointsAdjacent(pj,pr) != nullptr && tr1->PointsAdjacent(pj,pr)->isLegal()){
        ntr2->sete3(tr1->PointsAdjacent(pj,pr)); // e3 pj -> pr
        ntr2->e3()->twoPointsEdgeAdjacentFlip(pj,pr,ntr2);
    }

    legalizeEdge(pr, pi, pk, ntr1, dag);
    legalizeEdge(pr, pk, pj, ntr2, dag);


}

/**
 * @brief Triangulation::TrianglesForValidation
 * @details function to set the triangulation fields for verification with the function provided
 */
void Triangulation::TrianglesForValidation(){
    this->_triangles.clear();
    this->_points.clear();
    int index = 0;
    int count = 0;

    unsigned int a = 0;
    unsigned int b = 1;
    unsigned int c = 2;

    for(Triangle* t: this->drawTriangles ){
        if(t->isLegal()){
            count++;


            this->setPoints(t->v1());
            this->setPoints(t->v2());
            this->setPoints(t->v3());

            this->resizeTriangles( count, 3);

            this->setTriangles(index, 0, a);
            a=a+3;
            this->setTriangles(index, 1, b);
            b=b+3;
            this->setTriangles(index, 2, c);
            c=c+3;

            index++;
        }
    }
}

/**
 * @brief Triangulation::setTriangles
 * @param index
 * @param c
 * @param position
 */
void Triangulation::setTriangles(int index, int c, unsigned int position ){
    _triangles(index, c) = position;
}
/**
 * @brief Triangulation::resizeTriangles
 * @param row
 * @param colum
 */
void Triangulation::resizeTriangles(int row,int colum){
    _triangles.resize(row, colum);
}
/**
 * @brief Triangulation::setPoints
 * @details insert the points in the vector
 * @param p
 */
void Triangulation::setPoints(const Point2Dd& p){

    _points.push_back(p);
}

/**
 * @brief Triangulation::getPoints
 * @return vector of triangle points
 */
std::vector<Point2Dd> Triangulation::getPoints(){
    return this->_points;
}

/**
 * @brief Triangulation::getTriangles
 * @return matrix with triangle points
 */
cg3::Array2D<unsigned int> Triangulation::getTriangles(){
    return this->_triangles;
}

