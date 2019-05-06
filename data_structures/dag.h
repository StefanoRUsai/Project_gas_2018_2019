#ifndef DAG_H
#define DAG_H

#include "triangle.h"

class Dag{

private:
    Triangle* triangle = nullptr; //informazione
    //figli, al massimo sono 3 come da slide
    Dag* childOne = nullptr;
    Dag* childTwo = nullptr;
    Dag* childThree = nullptr;

public:
    Dag();
    Dag(Triangle* triangle);
    ~Dag();

    Dag* getChildOne() const;
    Dag* getChildTwo() const;
    Dag* getChildThree() const;
    Triangle* getTriangle() const;

    void setChildOne(Dag* node);
    void setChildTwo(Dag* node);
    void setChildThree(Dag* node);
    void setTriangle(Triangle* triangle);
    
    //per comparare
    bool operator == (const Dag& node);

    void add(Dag* node);
    //navigazione del grafo per controllare dove si trova il punto in oggetto
    Dag* navigateGraph(const cg3::Point2Dd& point);
    //controllo se il punto è contenuto dentro il triangolo



};

#endif // DAG_H
