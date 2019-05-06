#include <cg3/viewer/mainwindow.h>
#include "managers/delaunaymanager.h"
#include <data_structures/triangle.h>

int main(int argc, char *argv[]) {

    CG3_SUPPRESS_WARNING(argc);
    CG3_SUPPRESS_WARNING(argv);
/*
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
    */
    cg3::Point2Dd p1(2,3);
    cg3::Point2Dd p2(4,4);
    cg3::Point2Dd p3(5,6);

    Triangle triangolo(&p1,&p2,&p3);
    std::cout<<"sto stampando esattamente qui"<<std::endl;

    return 0;
}
