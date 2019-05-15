#include <cg3/viewer/mainwindow.h>
#include "managers/delaunaymanager.h"

#include <data_structures/triangle.h>
#include <data_structures/node.h>
#include <data_structures/dag.h>

using namespace delaunay;

int main(int argc, char *argv[]) {

    CG3_SUPPRESS_WARNING(argc);
    CG3_SUPPRESS_WARNING(argv);

    QApplication app(argc, argv);
    cg3::viewer::MainWindow gui;  //Main window, it contains QGLViewer canvas
    gui.set2DMode(true);
    gui.setSelectLeftButton();

    DelaunayManager dm(&gui);
    gui.addManager(&dm, "Delaunay Manager");

    //Show the GUI
    gui.updateGlCanvas();
    gui.show();

    return app.exec();

/*

    Point2Dd p1(2,2);
    Point2Dd p2(4,2);
    Point2Dd p3(3,8);

    Point2Dd p4(3,2);


    delaunay::Triangle triangolo(&p1,&p2,&p3);

    triangolo.printTriangle();

    Node node1;
    Node node2;
    Node node3;

    if(triangolo.controlPoint2(p4))
        std::cout<<"true"<<std::endl;
    else
        std::cout<<"false"<<std::endl;
    return 0;
    */
}
