#include <cg3/viewer/mainwindow.h>

#include "managers/voronoimanager.h"

int main(int argc, char *argv[]) {
    CG3_SUPPRESS_WARNING(argc);
    CG3_SUPPRESS_WARNING(argv);

    QApplication app(argc, argv);

    //Main window, it contains QGLViewer canvas
    cg3::viewer::MainWindow gui;

    //Set MainWindow options
    gui.set2DMode(true); //2D mode
    gui.setSelectLeftButton(); //Enable picking

    //Voronoi manager initialization
    VoronoiManager vm(&gui);
    gui.addManager(&vm, "Voronoi Manager");

    //Show the GUI
    gui.updateGlCanvas();
    gui.show();

    return app.exec();
}
