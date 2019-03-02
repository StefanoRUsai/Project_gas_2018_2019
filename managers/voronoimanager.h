#ifndef VORONOIMANAGER_H
#define VORONOIMANAGER_H

#include <QFrame>

#include <cg3/viewer/mainwindow.h>

#include <cg3/viewer/drawable_objects/2d/drawable_bounding_box2d.h>


namespace Ui {
    class VoronoiManager;
}

class VoronoiManager : public QFrame {
    Q_OBJECT

public:

    /* ----- Constructors/destructors ----- */

    explicit VoronoiManager(QWidget *parent = 0);
    ~VoronoiManager();


private:

    /* ----- Private fields ----- */

    //UI fields
    Ui::VoronoiManager *ui;
    cg3::viewer::MainWindow& mainWindow;    

    //It is const because, once defined and initialized, it will never change!
    const cg3::DrawableBoundingBox2D boundingBox;

    //Vector of points (the input of the algorithm)
    std::vector<cg3::Point2Dd> points;


    //Declare your attributes here
    /*****************************************/


    /*****************************************/




    /* ----- Private main methods ----- */

    void computeVoronoiDiagram(const std::vector<cg3::Point2Dd>& points);
    void clearVoronoiDiagram();

    void drawVoronoiDiagram();
    void eraseDrawnVoronoiDiagram();


    //Declare your private methods here if you need some
    /*****************************************/


    /*****************************************/



    /* ----- Private utility methods ----- */

    void fitScene();
    void launchAlgorithmAndMeasureTime();


private slots:

    /* ----- UI slots for loading points ----- */

    void on_loadPointsPushButton_clicked();
    void on_clearPointsPushButton_clicked();

    void point2DClicked(const cg3::Point2Dd& p);



    /* ----- UI slots for utilities ----- */

    void on_enablePickingCheckBox_stateChanged(int arg1);
    void on_resetScenePushButton_clicked();

    void on_generatePointsFilePushButton_clicked();
};

#endif // VORONOIMANAGER_H
