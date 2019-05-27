#include "node.h"
#include "triangulation.h"
#include "triangle.h"

#include <utils/delaunay_checker.h>

using namespace delaunay;
Triangulation::Triangulation(){}


std::vector<delaunay::Triangle*> Triangulation::getDrawTriangles(){
    return drawTriangles;
}

void Triangulation::addDrawTriangles(delaunay::Triangle* t){
    t->setIndex(drawTriangles.size());
    drawTriangles.push_back(t);
}

void Triangulation::unionEdge(const Point2Dd& point, Dag* dag){
    delaunay::Node *node=dag->navigateGraph(point, flag);
    delaunay::Triangle *triangle = node->t();

    //triangolazione partendo da un solo nodo

    if (this->flag==0) this->subdivisionTriangle(point,triangle, node, dag);
    if (this->flag==1) this->subdivisionTriangleDoubleE1(point,triangle, node, dag);
    if (this->flag==2) this->subdivisionTriangleDoubleE2(point,triangle, node, dag);
    if (this->flag==3) this->subdivisionTriangleDoubleE3(point,triangle, node, dag);


    //triangolazione partendo da 2 nodi
}
//suddivisione in 3 triangoli caso normale
void Triangulation::subdivisionTriangle(const Point2Dd& point, Triangle* triangle, Node* node, Dag* dag){

    delaunay::Triangle* tr1 = Triangulation::createTriangle(triangle->v1(), triangle->v2(), point,   node, dag);
    delaunay::Triangle* tr2 = Triangulation::createTriangle(point, triangle->v2(), triangle->v3(), node, dag);
    delaunay::Triangle* tr3 = Triangulation::createTriangle(triangle->v1(), point, triangle->v3(), node, dag);
    this->addDrawTriangles(tr1);
    if(triangle->e1()!=nullptr) tr1->sete1(triangle->e1());
    tr1->sete2(tr2);
    tr1->sete3(tr3);
    this->addDrawTriangles(tr2);
    if(triangle->e2()!=nullptr) tr2->sete2(triangle->e2());
    tr2->sete1(tr1);
    tr2->sete3(tr3);
    this->addDrawTriangles(tr3);
    if(triangle->e3()!=nullptr) tr3->sete3(triangle->e3());
    tr3->sete1(tr1);
    tr3->sete2(tr2);

    //legalizeEdge(const Point2Dd& pr, const Point2Dd& pi, const Point2Dd& pj, Triangle* t){


    legalizeEdge(point, triangle->v1(), triangle->v2(), tr1, dag);
    legalizeEdge(point, triangle->v2(), triangle->v3(), tr2, dag);
    legalizeEdge(point, triangle->v3(), triangle->v1(), tr3, dag);

}

//suddivisione in 4 triangoli partendolo dall'edge 1
//ricordandoci che i triangoli sono creati in senso anti orario la costruzione dovrebbe avenire nel modo seguente
void Triangulation::subdivisionTriangleDoubleE1(const Point2Dd& point, Triangle* triangle, Node* node, Dag* dag){

    delaunay::Triangle* tr1_1 = Triangulation::createTriangle(triangle->v1(),  point, triangle->v3(), node, dag);
    delaunay::Triangle* tr1_2 = Triangulation::createTriangle(point, triangle->v2(), triangle->v3(), node, dag);
    delaunay::Triangle* tr2_1 = nullptr;
    delaunay::Triangle* tr2_2 = nullptr;




    //cerco il vertice opposto v1==v3 e v2==v2 restituisco v1 per via del senso del triangolo
    if (triangle->v1() == triangle->e1()->v3() && triangle->v2() == triangle->e1()->v2()){

        tr2_1 = Triangulation::createTriangle(triangle->e1()->v1(), point, triangle->v1(), triangle->e1()->node(), dag);
        tr2_2 = Triangulation::createTriangle(triangle->e1()->v1(),  triangle->v2(), point,  triangle->e1()->node(), dag);

        //adiacenza triangolo basso sinistra
        tr2_1->sete1(tr2_2);
        tr2_1->sete2(tr1_1);
        if(triangle->e1()->e3()!=nullptr) tr2_1->sete3(triangle->e1()->e3());
        //adiacenza triangolo basso destra
        if(triangle->e1()->e1()!=nullptr) tr2_2->sete1(triangle->e1()->e1());
        tr2_2->sete2(tr1_2);
        tr2_2->sete3(tr2_1);

    }
    //cerco il vertice opposto v1==v1 e v2==v3 restituisco v2 per via del senso del triangolo
    if (triangle->v1() == triangle->e1()->v1() && triangle->v2() == triangle->e1()->v3()){
        tr2_1 = Triangulation::createTriangle(triangle->e1()->v2(), point, triangle->v1(), triangle->e1()->node(), dag);
        tr2_2 = Triangulation::createTriangle(triangle->e1()->v2(),  triangle->v2(),point,  triangle->e1()->node(), dag);

        //adiacenza triangolo basso sinistra
        tr2_1->sete1(tr2_2);
        tr2_1->sete2(tr1_1);
        if(triangle->e1()->e1()!=nullptr) tr2_1->sete3(triangle->e1()->e1());
        //adiacenza triangolo basso destra
        if(triangle->e1()->e2()!=nullptr) tr2_2->sete1(triangle->e1()->e2());
        tr2_2->sete2(tr1_2);
        tr2_2->sete3(tr2_1);

    }

        //cerco il vertice opposto v1==v2 e v2==v1 restituisco v3 per via del senso del triangolo
    if (triangle->v1() == triangle->e1()->v2() && triangle->v2() == triangle->e1()->v1()){
            tr2_1 = Triangulation::createTriangle(triangle->e1()->v3(), point, triangle->v1(), triangle->e1()->node(), dag);
            tr2_2 = Triangulation::createTriangle(triangle->e1()->v3(),  triangle->v2(),point,  triangle->e1()->node(), dag);

            //adiacenza triangolo basso sinistra
            tr2_1->sete1(tr2_2);
            tr2_1->sete2(tr1_1);
            if(triangle->e1()->e1()!=nullptr) tr2_1->sete3(triangle->e1()->e1());
            //adiacenza triangolo basso destra
            if(triangle->e1()->e2()!=nullptr) tr2_2->sete1(triangle->e1()->e2());
            tr2_2->sete2(tr1_2);
            tr2_2->sete3(tr2_1);
    }

    //adiacenza triangolo alto sinistra
    tr1_1->sete1(tr2_1);
    tr1_1->sete2(tr1_2);
    if(triangle->e3()!=nullptr) tr1_1->sete3(triangle->e3());
    //adiacenza triangolo alto destra
    tr1_2->sete1(tr2_2);
    if(triangle->e2()!=nullptr) tr1_2->sete2(triangle->e2());
    tr1_2->sete3(tr1_1);


    this->addDrawTriangles(tr1_1);
    this->addDrawTriangles(tr1_2);
    this->addDrawTriangles(tr2_1);
    this->addDrawTriangles(tr2_2);
    this->flag=0;
}

//suddivisione in 4 triangoli partendolo dall'edge 2
//ricordandoci che i triangoli sono creati in senso anti orario la costruzione dovrebbe avenire nel modo seguente
void Triangulation::subdivisionTriangleDoubleE2(const Point2Dd& point, Triangle* triangle, Node* node, Dag* dag){

    delaunay::Triangle* tr1_1 = Triangulation::createTriangle(triangle->v1(), triangle->v2(), point, node, dag);
    delaunay::Triangle* tr1_2 = Triangulation::createTriangle(triangle->v1(), point, triangle->v3(),  node, dag);

    delaunay::Triangle* tr2_1 = nullptr;
    delaunay::Triangle* tr2_2 = nullptr;

    //cerco il vertice opposto v2==v1 e v3==v3 restituisco v2 per via del senso del triangolo
    if (triangle->v2() == triangle->e2()->v1() && triangle->v3() == triangle->e2()->v3()){
            tr2_1 = Triangulation::createTriangle( triangle->e2()->v1(), triangle->e2()->v2(), point,  triangle->e2()->node(), dag);
            tr2_2 = Triangulation::createTriangle( point, triangle->e2()->v2(), triangle->e2()->v3(), triangle->e2()->node(), dag);

            if(triangle->e2()->e1()!=nullptr) tr2_1->sete1(triangle->e2()->e1());
            tr2_1->sete2(tr2_2);
            tr2_1->sete3(tr1_1);

            tr2_2->sete1(tr2_1);
            if(triangle->e2()->e2()!=nullptr) tr2_2->sete2(triangle->e2()->e2());
            tr2_2->sete3(tr1_2);


    }
    //cerco il vertice opposto v2==v2 e v3==v1 restituisco v3 per via del senso del triangolo
    if (triangle->v2() == triangle->e2()->v2() && triangle->v3() == triangle->e2()->v1()){
        tr2_1 = Triangulation::createTriangle(triangle->e2()->v2(), triangle->e2()->v3(), point, triangle->e2()->node(), dag);
        tr2_2 = Triangulation::createTriangle(point, triangle->e2()->v3(),triangle->e2()->v1(),  triangle->e2()->node(), dag);

        if(triangle->e2()->e2()!=nullptr) tr2_1->sete1(triangle->e2()->e2());
        tr2_1->sete2(tr2_2);
        tr2_1->sete3(tr1_1);

        tr2_2->sete1(tr2_1);
        if(triangle->e2()->e3()!=nullptr) tr2_2->sete2(triangle->e2()->e3());
        tr2_2->sete3(tr1_2);

    }
        //cerco il vertice opposto v2==v3 e v3==v2 restituisco v1 per via del senso del triangolo
    if (triangle->v2() == triangle->e2()->v3() && triangle->v3() == triangle->e2()->v2()){
            tr2_1 = Triangulation::createTriangle(triangle->e2()->v3(), triangle->e2()->v1(), point, triangle->e2()->node(), dag);
            tr2_2 = Triangulation::createTriangle(point, triangle->e2()->v1(), triangle->e2()->v2(),  triangle->e2()->node(), dag);

            if(triangle->e2()->e3()!=nullptr) tr2_1->sete1(triangle->e2()->e3());
            tr2_1->sete2(tr2_2);
            tr2_1->sete3(tr1_1);

            tr2_2->sete1(tr2_1);
            if(triangle->e2()->e1()!=nullptr) tr2_2->sete2(triangle->e2()->e1());
            tr2_2->sete3(tr1_2);
    }


    if(triangle->e1()!=nullptr) tr1_1->sete1(triangle->e1());
    tr1_1->sete2(tr2_1);
    tr1_1->sete3(tr1_2);

    tr1_2->sete1(tr1_1);
    tr1_2->sete2(tr2_2);
    if(triangle->e3()!=nullptr) tr2_1->sete3(triangle->e3());

    this->addDrawTriangles(tr1_1);
    this->addDrawTriangles(tr1_2);
    this->addDrawTriangles(tr2_1);
    this->addDrawTriangles(tr2_2);


    this->flag=0;
}

//suddivisione in 4 triangoli partendolo dall'edge 3
//ricordandoci che i triangoli sono creati in senso anti orario la costruzione dovrebbe avenire nel modo seguente
void Triangulation::subdivisionTriangleDoubleE3(const Point2Dd& point, Triangle* triangle, Node* node, Dag* dag){

    delaunay::Triangle* tr1_1 = Triangulation::createTriangle(triangle->v1(), triangle->v2(), point, node, dag);
    delaunay::Triangle* tr1_2 = Triangulation::createTriangle(point, triangle->v2(), triangle->v3(), node, dag);


    delaunay::Triangle* tr2_1 = nullptr;
    delaunay::Triangle* tr2_2 = nullptr;
    //cerco il vertice opposto v1==v1 e v3==v2 restituisco v3 per via del senso del triangolo
    if (triangle->v1() == triangle->e3()->v1() && triangle->v3() == triangle->e3()->v2()){
        tr2_1 = Triangulation::createTriangle(triangle->e3()->v1(), point, triangle->e3()->v3(), triangle->e3()->node(), dag);
        tr2_2 = Triangulation::createTriangle(point, triangle->e3()->v2(),  triangle->e3()->v3(),  triangle->e3()->node(), dag);

        tr2_1->sete1(tr1_1);
        tr2_1->sete2(tr2_2);
        if(triangle->e3()->e3()!=nullptr) tr2_1->sete3(triangle->e3()->e3());

        tr2_2->sete1(tr1_2);
        if(triangle->e3()->e2()!=nullptr) tr2_2->sete2(triangle->e3()->e2());
        tr2_2->sete3(tr2_1);
    }
    //cerco il vertice opposto v1==v2 e v3==v3 restituisco v1 per via del senso del triangolo
    if (triangle->v1() == triangle->e3()->v2() && triangle->v3() == triangle->e3()->v3()){
        tr2_1 = Triangulation::createTriangle(triangle->e3()->v2(), point, triangle->e3()->v1(), triangle->e3()->node(), dag);
        tr2_2 = Triangulation::createTriangle(point,  triangle->e3()->v3(), triangle->e3()->v1(),  triangle->e3()->node(), dag);

        tr2_1->sete1(tr1_1);
        tr2_1->sete2(tr2_2);
        if(triangle->e3()->e2()!=nullptr) tr2_1->sete3(triangle->e3()->e2());

        tr2_2->sete1(tr1_2);
        if(triangle->e3()->e3()!=nullptr) tr2_2->sete2(triangle->e3()->e3());
        tr2_2->sete3(tr2_1);
    }

    //cerco il vertice opposto v1==v3 e v3==v1 restituisco v2 per via del senso del triangolo
    if (triangle->v1() == triangle->e3()->v2() && triangle->v2() == triangle->e3()->v1()){
            tr2_1 = Triangulation::createTriangle(triangle->e3()->v3(), point, triangle->e3()->v2(), triangle->e3()->node(), dag);
            tr2_2 = Triangulation::createTriangle(point, triangle->e3()->v1(),  triangle->v2(),  triangle->e3()->node(), dag);

            tr2_1->sete1(tr1_1);
            tr2_1->sete2(tr2_2);
            if(triangle->e3()->e2()!=nullptr) tr2_1->sete3(triangle->e3()->e2());

            tr2_2->sete1(tr1_2);
            if(triangle->e3()->e1()!=nullptr) tr2_2->sete2(triangle->e3()->e1());
            tr2_2->sete3(tr2_1);
    }


    if(triangle->e1()!=nullptr) tr1_1->sete1(triangle->e1());
    tr1_1->sete2(tr1_2);
    tr1_1->sete3(tr2_1);

    tr1_2->sete1(tr1_1);
    if(triangle->e2()!=nullptr) tr2_1->sete2(triangle->e2());
    tr1_2->sete3(tr2_2);

    this->addDrawTriangles(tr1_1);
    this->addDrawTriangles(tr1_2);
    this->addDrawTriangles(tr2_1);
    this->addDrawTriangles(tr2_2);


    this->flag=0;
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

    Triangle* adjacent = nullptr;

    if(t->e1() != nullptr){
        if(t->e1()->twoPointsAdjacent(pi, pj))
            adjacent = t->e1();
    }
    if(t->e2() != nullptr){
        if(t->e2()->twoPointsAdjacent(pi, pj))
            adjacent = t->e2();
    }
    if(t->e3() != nullptr){
        if(t->e3()->twoPointsAdjacent(pi, pj))
            adjacent = t->e3();
    }

    if(adjacent != nullptr){
        if(DelaunayTriangulation::Checker::isPointLyingInCircle(adjacent->v1(), adjacent->v2(), adjacent->v3(), pr, false)){
            t->setIllegal();
            adjacent->setIllegal();
            edgeFlip(pr, pi, pj, t, adjacent, dag);
        }
     }

}


void Triangulation::edgeFlip(const Point2Dd& pr, const Point2Dd& pi, const Point2Dd& pj, Triangle* tr1, Triangle* tr2, Dag* dag ){

    Triangle* ntr1 = nullptr;
    Triangle* ntr2 = nullptr;

    const Point2Dd pk = tr2->thirdpoint(pi, pj);

    ntr1 = createTriangle(pr, pi, pk, tr1->node(), tr2->node(), dag );
    ntr2 = createTriangle(pr, pk, pj, tr1->node(), tr2->node(), dag );
    //adjacent ntr1

    this->addDrawTriangles(ntr1);
    this->addDrawTriangles(ntr2);

    ntr1->sete3(ntr2); //e3 pk -> pr
    ntr1->sete1(ntr1->twoPointsAdjacentTriangle(pr,pi,tr1)); //e1 pr -> pi
    if (ntr1->e1()!=nullptr)
        ntr1->twoPointsAdjacentTriangle(pr,pi,tr1)->twoPointsEdgeAdjacentFlip(pr,pi,ntr1); //triangolo ed edge opposto
    ntr1->sete2(ntr1->twoPointsAdjacentTriangle(pi,pk,tr2)); //e2 pi -> pk
    if (ntr1->e2()!=nullptr)
        ntr1->twoPointsAdjacentTriangle(pi,pk,tr2)->twoPointsEdgeAdjacentFlip(pi,pk,ntr1);

    ntr2->sete1(ntr1); // e1 pr -> pk
    ntr2->sete2(ntr2->twoPointsAdjacentTriangle(pk,pj,tr2)); // e2 pk -> pj
    if (ntr2->e2()!=nullptr)
        ntr2->twoPointsAdjacentTriangle(pk,pj,tr2)->twoPointsEdgeAdjacentFlip(pk,pj,ntr2); // triangolo ed edge opposto
    ntr2->sete3(ntr2->twoPointsAdjacentTriangle(pj,pr,tr1)); // e3 pj -> pr
    if (ntr1->e3()!=nullptr)
        ntr2->twoPointsAdjacentTriangle(pj,pr,tr1)->twoPointsEdgeAdjacentFlip(pj,pr,ntr2);

    legalizeEdge(pr, pi, pk, ntr1, dag);
    legalizeEdge(pr, pk, pj, ntr2, dag);

}
