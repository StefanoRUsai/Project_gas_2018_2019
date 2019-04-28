#ifndef DAG_H
#define DAG_H

#include <data_structures/triangle.h>

class Dag{

private:
    Triangle* tr = nullptr;
    Dag* childOne = nullptr;
    Dag* childTwo = nullptr;
    Dag* childThree = nullptr;

public:
    Dag();
    Dag(Triangle* tr);
    ~Dag();

    Dag* getChildOne() const;
    Dag* getChildTwoo() const;
    Dag* getChildTrhee() const;
    Triangle* getTriangle() const;

    void setChildOne(Dag* node);
    void setChildTwo(Dag* node);
    void setChildThree(Dag* node);
    void setTriangle(Triangle* triangle);


};

#endif // DAG_H
