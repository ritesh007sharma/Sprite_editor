#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "framecontainer.h"
#include <QFileDialog>
#include "load.h"
#include "save.h"
#include "gifexport.h"


namespace Ui {
class MainWindow;
}

/**
 * This class manages the tools utilized in the menu bar as well as integrating in the other widgets/
 * components within the spite edtior.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    /**
     * UI pointer for the interface
     */
    Ui::MainWindow *ui;

    /**
     * The model
     */
    FrameContainer frames;

private slots:
    /**
     * Emits a signal to notify that the user has selected the load button.
     */
    void on_loadButton_clicked();

    /**
     * Emits a signal to notify that the user has selected the save button.
     */
    void on_saveButton_clicked();

    /**
     * Emits a signal to notify that the user has selected the export button.
     */
    void on_exportToGIF_clicked();

public:
    /**
     * MainWindow Constructor auto generated by QT.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * MainWindow destructer
     */
    ~MainWindow();

signals:
    /**
     * Emits the current frame in the editor.
     */
    void sendFrame(QImage);

    /**
     * Loads the sprite editor file from a specified file path.
     */
    void loadFile(QString);

    /**
     * Saves the frames into a JSON format.
     */
    void saveFile(QString, std::vector<QImage>, int);

    /**
     * Exports the frames in a GIF format.
     */
    void exportFile(std::vector<QImage>, int, QString);

};
#endif
