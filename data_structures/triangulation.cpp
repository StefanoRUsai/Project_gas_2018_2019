#include "node.h"
#include "triangulation.h"
#include "triangle.h"

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
}

//suddivisione in 4 triangoli partendolo dall'edge 1
//ricordandoci che i triangoli sono creati in senso anti orario la costruzione dovrebbe avenire nel modo seguente
void Triangulation::subdivisionTriangleDoubleE1(const Point2Dd& point, Triangle* triangle, Node* node, Dag* dag){

    delaunay::Triangle* tr1_1 = Triangulation::createTriangle(triangle->v1(),  point, triangle->v3(), node, dag);
    delaunay::Triangle* tr1_2 = Triangulation::createTriangle(point, triangle->v2(), triangle->v3(), node, dag);


     delaunay::Triangle* tr2_1 = nullptr;
    delaunay::Triangle* tr2_2 = nullptr;
    //cerco il vertice opposto v1==v1 e v2==v3 restituisco v2 per via del senso del triangolo
    if (triangle->v1() == triangle->e1()->v1() && triangle->v2() == triangle->e1()->v3()){

            tr2_1 = Triangulation::createTriangle(triangle->e1()->v2(), point, triangle->v1(), triangle->e1()->node(), dag);
            tr2_2 = Triangulation::createTriangle(triangle->e1()->v2(),  triangle->v2(),point,  triangle->e1()->node(), dag);
    }
        //cerco il vertice opposto v1==v3 e v2==v2 restituisco v2 per via del senso del triangolo
    if (triangle->v1() == triangle->e1()->v3() && triangle->v2() == triangle->e1()->v2()){

        tr2_1 = Triangulation::createTriangle(triangle->e1()->v1(), point, triangle->v1(), triangle->e1()->node(), dag);
        tr2_2 = Triangulation::createTriangle(triangle->e1()->v1(),  triangle->v2(), point,  triangle->e1()->node(), dag);
    }
        //cerco il vertice opposto v1==v2 e v2==v1 restituisco v3 per via del senso del triangolo
    if (triangle->v1() == triangle->e1()->v2() && triangle->v2() == triangle->e1()->v1()){
            tr2_1 = Triangulation::createTriangle(triangle->e1()->v3(), point, triangle->v1(), triangle->e1()->node(), dag);
            tr2_2 = Triangulation::createTriangle(triangle->e1()->v3(),  triangle->v2(),point,  triangle->e1()->node(), dag);
    }

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

    }
    //cerco il vertice opposto v2==v2 e v3==v1 restituisco v3 per via del senso del triangolo
    if (triangle->v2() == triangle->e2()->v2() && triangle->v3() == triangle->e2()->v1()){
        tr2_1 = Triangulation::createTriangle(triangle->e2()->v2(), triangle->e2()->v2(), point, triangle->e2()->node(), dag);
        tr2_2 = Triangulation::createTriangle(triangle->e2()->v1(), point, triangle->e2()->v3(), triangle->e2()->node(), dag);
    }
        //cerco il vertice opposto v2==v3 e v3==v2 restituisco v1 per via del senso del triangolo
    if (triangle->v2() == triangle->e2()->v3() && triangle->v3() == triangle->e2()->v2()){
            tr2_1 = Triangulation::createTriangle(triangle->e2()->v3(), triangle->e2()->v1(), point, triangle->e2()->node(), dag);
            tr2_2 = Triangulation::createTriangle(triangle->e2()->v2(), point, triangle->e2()->v1(), triangle->e2()->node(), dag);
    }
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
    }
    //cerco il vertice opposto v1==v2 e v3==v3 restituisco v2 per via del senso del triangolo
    if (triangle->v1() == triangle->e3()->v2() && triangle->v3() == triangle->e3()->v3()){
        tr2_1 = Triangulation::createTriangle(triangle->e3()->v2(), point, triangle->e3()->v1(), triangle->e3()->node(), dag);
        tr2_2 = Triangulation::createTriangle(point,  triangle->e3()->v3(), triangle->e3()->v1(),  triangle->e3()->node(), dag);
    }

    //cerco il vertice opposto v1==v3 e v3==v1 restituisco v2 per via del senso del triangolo
    if (triangle->v1() == triangle->e3()->v2() && triangle->v2() == triangle->e3()->v1()){
            tr2_1 = Triangulation::createTriangle(triangle->e3()->v3(), point, triangle->e3()->v2(), triangle->e3()->node(), dag);
            tr2_2 = Triangulation::createTriangle(point, triangle->e3()->v1(),  triangle->v2(),  triangle->e3()->node(), dag);
    }

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
