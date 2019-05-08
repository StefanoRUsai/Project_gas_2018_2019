#ifndef TRIANGULATION_H
#define TRIANGULATION_H


#include <cg3/geometry/2d/point2d.h>
#include <data_structures/triangle.h>
#include <data_structures/dag.h>
using namespace cg3;
class Triangulation{
public:
    Triangulation(const std::vector<cg3::Point2Dd>& points, Node* root, Triangle* startTriangle);
    ~Triangulation();
  //  void createTriangle(Point2Dd* one,Point2Dd* two, Point2Dd* three, Dag* node);
  //  void createTriangle(Point2Dd* one,Point2Dd* two, Point2Dd* three, Dag* nodeOne, Dag* nodeTwo);
    void DelaunayAlgorithm();
    void createTriangle(Point2Dd one, Point2Dd two, Point2Dd three, Dag *node);
private:
    std::vector<cg3::Point2Dd> points; //punti in input per la triangolazione
    Dag dag;
    std::vector<Triangle*> triangles;  // triangoli da restituire

};

#endif // TRIANGULATION_H
