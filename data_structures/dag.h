#ifndef DAG_H
#define DAG_H

#include <data_structures/triangle.h>

class Dag{

private:
    Triangle* triangle = nullptr;
    Dag* childOne = nullptr;
    Dag* childTwo = nullptr;
    Dag* childThree = nullptr;

public:
    Dag();
    Dag(Triangle* triangle);
    ~Dag();

    Dag* getChildOne() const;
    Dag* getChildTwo() const;
    Dag* getChildTrhee() const;
    Triangle* getTriangle() const;

    void setChildOne(Dag* node);
    void setChildTwo(Dag* node);
    void setChildThree(Dag* node);
    void setTriangle(Triangle* triangle);

    static void add(Dag* node, Dag* old);

};

#endif // DAG_H
