#include "node.h"
#include "triangulation.h"
#include "triangle.h"

#include <utils/delaunay_checker.h>

using namespace delaunay;
Triangulation::Triangulation(){}


Triangulation::Triangulation(const Point2Dd& BT_P1, const Point2Dd& BT_P2, const Point2Dd& BT_P3){

    delaunay::Triangle start(BT_P3,BT_P1,BT_P2);
    Node node(&start);
    addDrawTriangles(&start);
    this->_dag.setNodes(&node);

}

Triangulation::Triangulation(Triangle* t, Node* node){

    addDrawTriangles(t);
    this->_dag.setNodes(node);
}



void Triangulation::addList(std::vector<Point2Dd>& points){
    for(Point2Dd point: points){

        this->unionEdge(point);
    }
}

void Triangulation::addPoint( Point2Dd& point){

    this->unionEdge(point);
}

std::vector<delaunay::Triangle*> Triangulation::getDrawTriangles(){
    return drawTriangles;
}

void Triangulation::addDrawTriangles(delaunay::Triangle* t){
    drawTriangles.push_back(t);
}


void Triangulation::unionEdge(const Point2Dd& point){
    delaunay::Node *node=this->_dag.navigateGraph(point, flag);
    delaunay::Triangle *triangle = node->t();

    //triangolazione partendo da un solo nodo

    if (this->flag==0) this->subdivisionTriangle(point,triangle, node, &_dag);
    if (this->flag==1) this->subdivisionTriangleDoubleE1(point,triangle, node, &_dag);
    if (this->flag==2) this->subdivisionTriangleDoubleE2(point,triangle, node, &_dag);
    if (this->flag==3) this->subdivisionTriangleDoubleE3(point,triangle, node, &_dag);


    //triangolazione partendo da 2 nodi
}
//suddivisione in 3 triangoli caso normale
void Triangulation::subdivisionTriangle(const Point2Dd& point, Triangle* triangle, Node* node, Dag* dag){

    delaunay::Triangle* tr1 = Triangulation::createTriangle(point, triangle->v1(), triangle->v2(),    node, dag);
    delaunay::Triangle* tr2 = Triangulation::createTriangle(point, triangle->v2(), triangle->v3(), node, dag);
    delaunay::Triangle* tr3 = Triangulation::createTriangle(point, triangle->v3(), triangle->v1(), node, dag);

    triangle->setIllegal();

    tr1->sete1(tr3);
    tr1->sete2(triangle->PointsAdjacent(tr1->v2(),tr1->v3()));
    if(triangle->PointsAdjacent(tr1->v2(),tr1->v3()) != nullptr)
        triangle->PointsAdjacent(tr1->v2(),tr1->v3())->twoPointsEdgeAdjacentFlip(tr1->v2(),tr1->v3(), tr1);
    tr1->sete3(tr2);

    tr2->sete1(tr1);
    tr2->sete2(triangle->PointsAdjacent(tr2->v2(),tr2->v3()));
    if(triangle->PointsAdjacent(tr2->v2(),tr2->v3()) != nullptr)
        triangle->PointsAdjacent(tr2->v2(),tr2->v3())->twoPointsEdgeAdjacentFlip(tr2->v2(),tr2->v3(), tr2);
    tr2->sete3(tr3);


    tr3->sete1(tr2);
    tr3->sete2(triangle->PointsAdjacent(tr3->v2(),tr3->v3()));
    if(triangle->PointsAdjacent(tr3->v2(),tr3->v3()) != nullptr)
        triangle->PointsAdjacent(tr3->v2(),tr3->v3())->twoPointsEdgeAdjacentFlip(tr3->v2(),tr3->v3(), tr3);
    tr3->sete3(tr1);

    legalizeEdge(point, triangle->v1(), triangle->v2(), tr1, dag);
    legalizeEdge(point, triangle->v2(), triangle->v3(), tr2, dag);
    legalizeEdge(point, triangle->v3(), triangle->v1(), tr3, dag);

}

//suddivisione in 4 triangoli partendolo dall'edge 3
//ricordandoci che i triangoli sono creati in senso anti orario la costruzione dovrebbe avenire nel modo seguente
void Triangulation::subdivisionTriangleDoubleE1(const Point2Dd& point, Triangle* triangle, Node* node, Dag* dag){

    delaunay::Triangle* tr1_1 = Triangulation::createTriangle(point, triangle->v2(), triangle->v3(), node, dag);
    delaunay::Triangle* tr1_2 = Triangulation::createTriangle(point, triangle->v3(), triangle->v1(), node, dag);


    delaunay::Triangle* tr2_1 = nullptr;
    delaunay::Triangle* tr2_2 = nullptr;

    const Point2Dd tp = triangle->e1()->thirdpoint(triangle->v1(), triangle->v2());

    tr2_1 = Triangulation::createTriangle(point, tp, triangle->v2(), triangle->e1()->node(), dag);
    tr2_2 = Triangulation::createTriangle(point, triangle->v1(), tp, triangle->e1()->node(), dag);

    triangle->setIllegal();
    triangle->e1()->setIllegal();

    tr2_1->sete1(tr2_2);
    tr2_1->sete2(triangle->e1()->searchAdjacentTriangle(tp, triangle->v2()));
    if (triangle->e1()->searchAdjacentTriangle(tp, triangle->v2()) != nullptr)
        triangle->e1()->searchAdjacentTriangle(tp, triangle->v2())->twoPointsEdgeAdjacentFlip(tp, triangle->v2(), tr2_1);
    tr2_1->sete3(tr1_1);

    tr2_2->sete1(tr1_2);
    tr2_2->sete2(triangle->e1()->searchAdjacentTriangle(triangle->v1(), tp));
    if (triangle->e1()->searchAdjacentTriangle(tp, triangle->v2()) != nullptr)
        triangle->e1()->searchAdjacentTriangle(tp, triangle->v2())->twoPointsEdgeAdjacentFlip(tp, triangle->v2(), tr2_2);
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

    this->flag=0;


    legalizeEdge(point, triangle->v1(), triangle->v2(), tr1_1, dag);
    legalizeEdge(point, triangle->v3(), triangle->v1(), tr1_2, dag);
    legalizeEdge(point, triangle->v2(), tp, tr2_1, dag);
    legalizeEdge(point, tp, triangle->v3(), tr2_2, dag);
}


//suddivisione in 4 triangoli partendolo dall'edge 2
//ricordandoci che i triangoli sono creati in senso anti orario la costruzione dovrebbe avenire nel modo seguente
void Triangulation::subdivisionTriangleDoubleE2(const Point2Dd& point, Triangle* triangle, Node* node, Dag* dag){

    delaunay::Triangle* tr1_1 = Triangulation::createTriangle(point, triangle->v1(), triangle->v2(), node, dag);
    delaunay::Triangle* tr1_2 = Triangulation::createTriangle(point, triangle->v3(), triangle->v1(), node, dag);


    delaunay::Triangle* tr2_1 = nullptr;
    delaunay::Triangle* tr2_2 = nullptr;

    const Point2Dd tp = triangle->e2()->thirdpoint(triangle->v2(), triangle->v3());

    tr2_1 = Triangulation::createTriangle(point, triangle->v2(), tp, triangle->e2()->node(), dag);
    tr2_2 = Triangulation::createTriangle(point, tp, triangle->v3(),  triangle->e2()->node(), dag);


    triangle->setIllegal();
    triangle->e2()->setIllegal();


    tr2_1->sete1(tr1_1);
    tr2_1->sete2(triangle->e2()->searchAdjacentTriangle(triangle->v2(), tp));
    if (triangle->e2()->searchAdjacentTriangle(triangle->v2(), tp) != nullptr)
        triangle->e2()->searchAdjacentTriangle(triangle->v2(), tp)->twoPointsEdgeAdjacentFlip(triangle->v2(), tp, tr2_1);
    tr2_1->sete3(tr2_2);

    tr2_2->sete1(tr2_1);
    tr2_2->sete2(triangle->e2()->searchAdjacentTriangle(tp, triangle->v3()));
    if (triangle->e2()->searchAdjacentTriangle(tp, triangle->v3()) != nullptr)
        triangle->e2()->searchAdjacentTriangle(tp, triangle->v3())->twoPointsEdgeAdjacentFlip(tp, triangle->v3(), tr2_2);
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

    this->flag=0;


    legalizeEdge(point, triangle->v1(), triangle->v2(), tr1_1, dag);
    legalizeEdge(point, triangle->v3(), triangle->v1(), tr1_2, dag);
    legalizeEdge(point, triangle->v2(), tp, tr2_1, dag);
    legalizeEdge(point, tp, triangle->v3(), tr2_2, dag);

}

//suddivisione in 4 triangoli partendolo dall'edge 2
//ricordandoci che i triangoli sono creati in senso anti orario la costruzione dovrebbe avenire nel modo seguente
void Triangulation::subdivisionTriangleDoubleE3(const Point2Dd& point, Triangle* triangle, Node* node, Dag* dag){


    delaunay::Triangle* tr1_1 = Triangulation::createTriangle(point, triangle->v2(), triangle->v3(), node, dag);
    delaunay::Triangle* tr1_2 = Triangulation::createTriangle(point, triangle->v2(), triangle->v1(), node, dag);


    delaunay::Triangle* tr2_1 = nullptr;
    delaunay::Triangle* tr2_2 = nullptr;

    const Point2Dd tp = triangle->e3()->thirdpoint(triangle->v3(), triangle->v1());

    tr2_1 = Triangulation::createTriangle(point, triangle->v3(), tp, triangle->e3()->node(), dag);
    tr2_2 = Triangulation::createTriangle(point, tp, triangle->v1(),  triangle->e3()->node(), dag);


    triangle->setIllegal();
    triangle->e3()->setIllegal();


    tr2_1->sete1(tr1_1);
    tr2_1->sete2(triangle->e3()->searchAdjacentTriangle(triangle->v3(), tp));
    if (triangle->e3()->searchAdjacentTriangle(triangle->v3(), tp) != nullptr)
        triangle->e3()->searchAdjacentTriangle(triangle->v3(), tp)->twoPointsEdgeAdjacentFlip(triangle->v3(), tp, tr2_1);
    tr2_1->sete3(tr2_2);

    tr2_2->sete1(tr2_1);
    tr2_2->sete2(triangle->e2()->searchAdjacentTriangle(tp, triangle->v1()));
    if (triangle->e2()->searchAdjacentTriangle(tp, triangle->v1()) != nullptr)
        triangle->e2()->searchAdjacentTriangle(tp, triangle->v1())->twoPointsEdgeAdjacentFlip(tp, triangle->v1(), tr2_2);
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

    this->flag=0;


    legalizeEdge(point, triangle->v2(), triangle->v3(), tr1_1, dag);
    legalizeEdge(point, triangle->v2(), triangle->v1(), tr1_2, dag);
    legalizeEdge(point, triangle->v3(), tp, tr2_1, dag);
    legalizeEdge(point, tp, triangle->v1(), tr2_2, dag);


}



Triangle* Triangulation::createTriangle(const Point2Dd& one,const Point2Dd& two, const Point2Dd& three, Node *node, Dag *dag){
    Triangle* t = new Triangle(one, two, three);
    Node* n = new Node();
    n->setTriangle(t);
    t->setNode(n);
    dag->setNodes(n);
    node->add(n);
    return t;
}

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


void Triangulation::edgeFlip(const Point2Dd& pr, const Point2Dd& pi, const Point2Dd& pj, Triangle* tr1, Triangle* tr2, Dag* dag ){

    tr1->setIllegal();
    tr2->setIllegal();

    Triangle* ntr1 = nullptr;
    Triangle* ntr2 = nullptr;

    const Point2Dd pk = tr2->thirdpoint(pi, pj);

    if (pk != pi){

        ntr1 = createTriangle(pr, pi, pk, tr1->node(), tr2->node(), dag );
        ntr2 = createTriangle(pr, pk, pj, tr1->node(), tr2->node(), dag );

        ntr1->sete3(ntr2); //e3 pk -> pr
        ntr2->sete1(ntr1); // e1 pr -> pk

        if(tr1->PointsAdjacent(pr,pi) != nullptr && tr1->PointsAdjacent(pr,pi)->isLegal()){
            ntr1->sete1(tr1->PointsAdjacent(pr,pi)); //e1 pr -> pi
            tr1->PointsAdjacent(pr,pi)->twoPointsEdgeAdjacentFlip(pr,pi,ntr1); //triangolo ed edge opposto
        }

        if(tr2->PointsAdjacent(pi,pk) != nullptr && tr2->PointsAdjacent(pi,pk)->isLegal()){
            ntr1->sete2(tr2->PointsAdjacent(pj,pk)); //e2 pi -> pk
            tr2->PointsAdjacent(pi,pk)->twoPointsEdgeAdjacentFlip(pi,pk,ntr1);
        }


        if(tr2->PointsAdjacent(pk,pj) != nullptr && tr2->PointsAdjacent(pk,pj)->isLegal()){
            ntr2->sete2(tr2->PointsAdjacent(pk,pj)); // e2 pk -> pj
            tr2->PointsAdjacent(pk,pj)->twoPointsEdgeAdjacentFlip(pk,pj,ntr2); // triangolo ed edge opposto
        }

        if(tr1->PointsAdjacent(pj,pr) != nullptr && tr1->PointsAdjacent(pj,pr)->isLegal()){
            ntr2->sete3(tr1->PointsAdjacent(pj,pr)); // e3 pj -> pr
            tr1->PointsAdjacent(pj,pr)->twoPointsEdgeAdjacentFlip(pj,pr,ntr2);
        }

        legalizeEdge(pr, pi, pk, ntr1, dag);
        legalizeEdge(pr, pk, pj, ntr2, dag);
    }else {
        std::cout<<"non dovrei mai essere qui"<<std::endl;
    }
}


void Triangulation::TrianglesForValidation(){

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

void Triangulation::setTriangles(int index, int c, unsigned int position ){
    _triangles(index, c) = position;
}
void Triangulation::resizeTriangles(int row,int colum){
    _triangles.resize(row, colum);
}

void Triangulation::setPoints(Point2Dd p){

    _points.push_back(p);
}

std::vector<Point2Dd> Triangulation::getPoints(){
    return this->_points;
}
cg3::Array2D<unsigned int> Triangulation::getTriangles(){
    return this->_triangles;
}
