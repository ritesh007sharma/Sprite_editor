#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editorview.h"
#include "animatedpreview.h"
#include "editortools.h"
#include "drawingtools.h"
#include "framepreview.h"
#include "framepreviewscroll.h"
#include <QGridLayout>
#include <QPushButton>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout* layout = new QGridLayout;

    //instantiating all the other widgets/components witihn the application
    AnimatedPreview* animatedPrev = new AnimatedPreview();
    EditorView* eView = new EditorView();
    EditorTools* eTools = new EditorTools();
    DrawingTools* dTools = new DrawingTools();
    FramePreviewScroll* framePrevScroll = new FramePreviewScroll;
    Load *loadClass = new Load();
    Save *saveClass = new Save();
    GifExport *exGIF = new GifExport();
    QColorDialog* dialog = new QColorDialog;
    dialog->setOptions(QColorDialog::DontUseNativeDialog | QColorDialog::NoButtons);

    //Connections for the editor tools
    connect(eTools, &EditorTools::flipH,
            &frames, &FrameContainer::flipFrameH);
    connect(eTools, &EditorTools::flipV,
            &frames, &FrameContainer::flipFrameV);
    connect(eTools, &EditorTools::duplicate,
            &frames, &FrameContainer::duplicateFrame);
    connect(eTools, &EditorTools::addFrame,
            &frames, &FrameContainer::newFrame);
    connect(eTools, &EditorTools::scale,
            &frames, &FrameContainer::scaleFrames);
    connect(eTools, &EditorTools::resetFrame,
            &frames, &FrameContainer::clearFrame);
    connect(eTools, &EditorTools::removeFrame,
            &frames, &FrameContainer::deleteCurrentFrame);

    //Connections for the Colors pallete
    connect(dialog, &QColorDialog::currentColorChanged,
            eView->getEditor(), &Editor::changeColor);

    //Connections for the drawing tools
    connect(dTools, &DrawingTools::sendType,
            eView->getEditor(), &Editor::changeTool);

    //Connections from the frame preview to the editor frame
    connect(framePrevScroll->getFramePreview(), &FramePreview::sendFrameClicked,
            &frames, &FrameContainer::setCurrentFrame);

    //Receive added frames from the model
    connect(&frames, &FrameContainer::addFrame,
            eView->getEditor(), &Editor::changeFrame);
    connect(&frames, &FrameContainer::addFrame,
            framePrevScroll->getFramePreview(), &FramePreview::addFrame);
    //receive updated frames from model
    connect(&frames, &FrameContainer::sendFrame,
            eView->getEditor(), &Editor::changeFrame);
    connect(&frames, &FrameContainer::sendAnimatedFrame,
            animatedPrev, &AnimatedPreview::receiveDisplay);
    connect(&frames, &FrameContainer::sendFrame,
            framePrevScroll->getFramePreview(), &FramePreview::receiveFrame);
    connect(&frames, &FrameContainer::removeFrame,
            framePrevScroll->getFramePreview(), &FramePreview::deleteFrame);
    //receive updated size from model
    connect(&frames, &FrameContainer::addFrame,
            animatedPrev, &AnimatedPreview::addFrame);
    connect(&frames, &FrameContainer::removeFrame,
            animatedPrev, &AnimatedPreview::removeFrame);

    //Connections to drawing tools
    connect(eView->getEditor(), &Editor::fillPixel,
            &frames, &FrameContainer::fillPixel);
    connect(eView->getEditor(), &Editor::erasePixel,
            &frames, &FrameContainer::erase);
    connect(eView->getEditor(), &Editor::setPixel,
            &frames, &FrameContainer::setPixel);
    connect(eView->getEditor(), &Editor::drawLine,
            &frames, &FrameContainer::drawLine);

    //Connections from animatedpreview to the editor
    connect(animatedPrev, &AnimatedPreview::requestFrame,
            &frames, &FrameContainer::requestAnimatedFrame);

    //update dimensions
    connect(&frames, &FrameContainer::returnDimensions,
            eView->getEditor(), &Editor::setDim);

    //Connections for saving, loading, and exporting
    connect(this, &MainWindow::loadFile,
            loadClass, &Load::open);
    connect(this, &MainWindow::saveFile,
            saveClass, &Save::saveFile);
    connect(loadClass, &Load::sendVectorOfFrames,
            &frames, &FrameContainer::loadFile);
    connect(this, &MainWindow::exportFile,
            exGIF, &GifExport::exportAsGIF);

    layout->addWidget(eView, 0, 1, 5, 1);
    layout->addWidget(eTools, 3, 4, 1, 2);
    layout->addWidget(dTools, 3, 3, 1, 1);
    layout->addWidget(animatedPrev, 0, 0, 1, 1);
    layout->addWidget(framePrevScroll, 1, 0, 4, 1);
    layout->addWidget(dialog, 0, 3, 3, 4);

    ui->centralWidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    QString filter = "ssp (*.ssp)";
    QString filePath = QFileDialog::getOpenFileName(this, "Load File","/home/", filter);
    if(!filePath.isEmpty())
    {
        emit loadFile(filePath);
    }
}

void MainWindow::on_saveButton_clicked()
{
    QString filter = "ssp (*.ssp)";
    QString filePath = QFileDialog::getSaveFileName(this, "Save As", "/home/", filter);

    if(!filePath.isEmpty())
    {
        filePath=filePath+".ssp";
        emit saveFile(filePath, frames.getFrames(), frames.getDimension());
    }
}

void MainWindow::on_exportToGIF_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save As", "/home/");
    if(!filePath.isEmpty())
    {
        filePath=filePath + ".gif";
        emit exportFile(frames.getFrames(),frames.getDimension(),filePath);
    }
}
