#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <cg3/geometry/2d/point2d.h>
#include <data_structures/triangle.h>
#include <data_structures/dag.h>

class Triangulation{
public:
    Triangulation();
    ~Triangulation();
    Triangle* createTriangle(cg3::Point2Dd* one,cg3::Point2Dd* two, cg3::Point2Dd* three, Dag* node);

private:
    std::vector<cg3::Point2Dd*> points; //punti in input per la triangolazione
    std::vector<Dag*> nodes; // nodi del dag
    std::vector<Triangle*> triangles;  // triangoli da restituire

};

#endif // TRIANGULATION_H
