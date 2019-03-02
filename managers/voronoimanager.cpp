#include "voronoimanager.h"
#include "ui_voronoimanager.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

#include <ctime>

#include "utils/fileutils.h"
#include <cg3/data_structures/arrays/arrays.h>
#include <cg3/utilities/timer.h>

//Limits for the bounding box
//It defines where points can be added
//Do not change the following line
#define BOUNDINGBOX 1e+6

//Constants for scene reset
//Do not change the following lines
const double SCENERADIUS = BOUNDINGBOX;
const cg3::Pointd SCENECENTER(0,0,0);






//----------------------------------------------------------------------------------------------
//                         You have to write your code in the area below.
//----------------------------------------------------------------------------------------------



/* ----- Constructors/Destructors ----- */

/**
 * @brief Default constructor of the manager
 */
VoronoiManager::VoronoiManager(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::VoronoiManager),
    mainWindow((cg3::viewer::MainWindow&)*parent),
    boundingBox(cg3::Point2Dd(-BOUNDINGBOX, -BOUNDINGBOX),
                cg3::Point2Dd(BOUNDINGBOX, BOUNDINGBOX))    
{
    //***** NOTE: you probably need to initialize your objects in the constructor *****

    //UI setup
    ui->setupUi(this);
    connect(&mainWindow, SIGNAL(point2DClicked(cg3::Point2Dd)), this, SLOT(point2DClicked(cg3::Point2Dd)));

    //Setting options for the canvas
    mainWindow.disableRotation();
    mainWindow.setSelectLeftButton();

    //Add the drawable object to the mainWindow.
    //The mainWindow will take care of rendering the bounding box
    mainWindow.pushObj(&boundingBox, "Bounding box");

    //This updates the canvas (call it whenever you change or
    //add some drawable object)
    mainWindow.updateGlCanvas();

    fitScene();
}


/**
 * @brief Destructor of the manager
 */
VoronoiManager::~VoronoiManager() {
    //Try to avoid using dynamic objects whenever it is possible.
    //
    //In case you allocated dynamic objects in this manager, you
    //should delete (deallocate) all of them when the application
    //closes.
    //Remember that each class which allocates dynamic objects
    //should implement a destructor which deallocates them.    
    //
    //Example:
    //      delete dynamicObject;
    //      dynamicObject = nullptr;
    /*****************************************/

    /*****************************************/

    //When the manager is destroyed, the mainWindow should
    //not have any reference to drawable objects.
    //
    //Example:
    //      mainWindow.deleteObj(&voronoiDiagramDrawableObject);
    //  or
    //      mainWindow.deleteObj(pointerTo_VoronoiDiagramDrawableObject);
    //
    //Try to avoid using dynamic objects whenever it is possible.
    /*****************************************/

    /*****************************************/

    //Delete the bounding box drawable object
    mainWindow.deleteObj(&boundingBox);

    delete ui; //Delete interface
}



/* ----- Private main methods ----- */

/**
 * @brief Launch fortune algorithm for a vector of points.
 * Note that the vector could contain duplicates.
 * @param[in] points Vector of points
 */
void VoronoiManager::computeVoronoiDiagram(const std::vector<cg3::Point2Dd>& inputPoints) {
    //Launch your Fortune algorithm here on the vector "inputPoints" in input
    //(note that the vector could contain duplicates).
    //Here you should call an algorithm (obviously defined in another file!) which
    //fills your output Voronoi Diagram data structure.
    /*****************************************/

    /*****************************************/

    //You should delete this line after you implement the algorithm: it is
    //just needed to suppress the unused-variable warning
    CG3_SUPPRESS_WARNING(inputPoints);
}

/**
 * @brief Clear data of the Voronoi diagram
 */
void VoronoiManager::clearVoronoiDiagram() {
    //Clear here your Voronoi diagram data structure.
    /*****************************************/

    /*****************************************/
}



/**
 * @brief Draw the Voronoi diagram in the canvas
 */
void VoronoiManager::drawVoronoiDiagram() {
    //Note that you could keep a Drawable Voronoi diagram object always
    //rendered (even when it is empty), instead of deleting it from the main
    //window and re-draw it again.
    //Take as example DrawableBoundingBox2D in this manager (although it is const).
    //This is actually a good approach: if you choose it, you probably
    //do not need to write anything in the following area, since the canvas
    //will automatically draw the updated Voronoi diagram.
    //
    //Draw your Voronoi diagram in the canvas here if you choose another
    //approach.
    /*****************************************/

    /* Read carefully the above comments! */

    /*****************************************/

    //Canvas update
    mainWindow.updateGlCanvas();
}

/**
 * @brief Erase drawn Voronoi Diagram from the canvas
 */
void VoronoiManager::eraseDrawnVoronoiDiagram() {
    //Note that you could keep a Drawable Voronoi diagram object always
    //rendered (even when it is empty), instead of deleting it from the main
    //window and re-draw it again.
    //Take as example DrawableBoundingBox2D in this manager, even if it never
    //changes.
    //This is actually a good approach: if you choose it, you probably do
    //not need to write anything in the following area because you should
    //have cleared your Voronoi diagram some lines above. The canvas will
    //automatically draw the updated Voronoi diagram.
    //
    //Remove the Drawable Voronoi diagram object from the canvas
    //(mainWindow.deleteObj() which takes a reference) if you choose another
    //approach.
    //Deallocate it if you allocated it dynamically, even if you should try
    //to avoid using dynamic objects whenever it is possible.
    /*****************************************/

    /* Read carefully the above comments! */

    /*****************************************/

    //Canvas update
    mainWindow.updateGlCanvas();
}



//Define your private methods here if you need some
/*****************************************/


/*****************************************/






//----------------------------------------------------------------------------------------------
//              You will probably not need to write/edit code in the area below.
//----------------------------------------------------------------------------------------------


/* ----- Private utility methods ----- */

/**
 * @brief Launch the algorithm for computing the Voronoi diagram
 * on the input points (a vector) of this manager and measure
 * its time efficiency.
 */
void VoronoiManager::launchAlgorithmAndMeasureTime() { //Do not write code here
    //Output message
    std::cout << "Executing the algorithm for " << this->points.size() << " points..." << std::endl;

    //Timer for evaluating the efficiency of the algorithm
    cg3::Timer t("Voronoi diagram generation");

    //Launch fortune algorithm on the vector of input points
    computeVoronoiDiagram(this->points);

    //Timer stop and visualization (both on console and UI)
    t.stopAndPrint();
    ui->timeLabel->setNum(t.delay());

    std::cout << std::endl;
}

/**
 * @brief Change camera of the canvas to fit the scene
 * on the bounding box in which the points can be added.
 */
void VoronoiManager::fitScene() { //Do not write code here
    mainWindow.fitScene(SCENECENTER, SCENERADIUS);
}




/* ----- UI slots for loading points ----- */

/**
 * @brief Load points event handler.
 *
 * Load input points from a file.
 */
void VoronoiManager::on_loadPointsPushButton_clicked() { //Do not write code here
    //File selector
    QString filename = QFileDialog::getOpenFileName(nullptr,
                       "Open points",
                       ".",
                       "*.txt");

    if (!filename.isEmpty()) {
        //Clear current data
        clearVoronoiDiagram();

        //Delete from the canvas the Voronoi diagram
        eraseDrawnVoronoiDiagram();

        //Load input points in the vector (deleting the previous ones)
        this->points = FileUtils::getPointsFromFile(filename.toStdString());

        //Launch the algorithm on the current vector of points and measure
        //its efficiency with a timer
        launchAlgorithmAndMeasureTime();

        //Draw Voronoi diagram
        drawVoronoiDiagram();
    }
}

/**
 * @brief Clear points button event handler.
 *
 * It allows us to clear our Voronoi diagram input points.
 */
void VoronoiManager::on_clearPointsPushButton_clicked() { //Do not write code here
    //Clear the vector of points
    this->points.clear();

    //Clear current data
    clearVoronoiDiagram();

    //Delete from the canvas the Voronoi diagram
    eraseDrawnVoronoiDiagram();

    //Clear timer data
    ui->timeLabel->setText("");
}




/**
 * @brief Point 2D clicked handler.
 *
 * This method is called whenever the user clicks the canvas.
 * The coordinates (x and y) of the clicked point are given by
 * the 2D point p.
 *
 * @param[in] p Point clicked
 */
void VoronoiManager::point2DClicked(const cg3::Point2Dd& p) { //Do not write code here
    if (!boundingBox.isInside(p)) {
        //Error message if the point is not inside the bounding box
        QMessageBox::warning(this, "Cannot insert point", "Point [" +
                             QString::number(p.x()) + "," + QString::number(p.y()) +
                             "] is not contained in the bounding box.");
        return;
    }
    else {
        //Uncomment the next line for a debug message about the clicked point
//        QMessageBox::information(this, "Point clicked", "Point [" +
//                                 QString::number(p.x()) + "," + QString::number(p.y()) +
//                                 "].");

        //Add the clicked point to the vector of points
        this->points.push_back(p);

        //Clear data
        clearVoronoiDiagram();

        //Delete from the canvas the Voronoi diagram
        eraseDrawnVoronoiDiagram();

        //Launch the algorithm on the current vector of points and measure
        //its efficiency with a timer
        launchAlgorithmAndMeasureTime();

        //Draw in the canvas the Voronoi diagram
        drawVoronoiDiagram();
    }
}




/* ----- UI slots for utilities ----- */

/**
 * @brief Enable picking checkbox handler.
 *
 * Checkbox to enable/disable the point clicking on the canvas.
 *
 * @param[in] arg1 It contains Qt::Checked if the checkbox is checked,
 * Qt::Unchecked otherwise
 */
void VoronoiManager::on_enablePickingCheckBox_stateChanged(int arg1) { //Do not write code here
    if (arg1 == Qt::Checked){
        mainWindow.setSelectLeftButton();
    }
    else {
        mainWindow.disableRotation();
    }
}

/**
 * @brief Reset scene event handler.
 *
 * It allows us to reset the camera of the canvas to
 * show/center the scene in the bounding box.
 */
void VoronoiManager::on_resetScenePushButton_clicked() { //Do not write code here
    fitScene();
}



/**
 * @brief Generate random points handler.
 *
 * With this button we can generate files that contains
 * points which are inside the bounding box.
 */
void VoronoiManager::on_generatePointsFilePushButton_clicked() { //Do not write code here
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(nullptr,
                       "File containing points",
                       ".",
                       "TXT(*.txt)", &selectedFilter);

    if (!filename.isEmpty()){
        int number = QInputDialog::getInt(
                    this,
                    tr("Generate file"),
                    tr("Number of random points:"), 1000, 0, 1000000000, 1);

        //Generate points and save them in the chosen file
        FileUtils::generateRandomPointFile(filename.toStdString(), BOUNDINGBOX, number);
    }
}
