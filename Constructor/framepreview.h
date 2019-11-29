#ifndef FRAMEPREVIEW_H
#define FRAMEPREVIEW_H

#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include "framelabel.h"

/**
 * This class displays all of the frames.
 */
class FramePreview : public QWidget
{
    Q_OBJECT

private:
    /**
     * Size of each individual frame
     */
    int displaySize;

    /**
     * Position of the current frame in the total list of frames.
     */
    int currentLabel;

    /**
     * List of all frames.
     */
    QVector<FrameLabel*> labels;

public:
    /**
     * Intializes all instance variables and sets up the layout of the widget.
     * Starts the preview with one default blank frame.
     */
    FramePreview();

    /**
     * Vertical box layout for frames.
     */
    QVBoxLayout* layout;

public slots:
    /**
     * receives changed frame from editor and updates the frame preview array (labels).
     */
    void receiveFrame(QPixmap, int);

    /**
     * Inserts a new frame into the frame preview array (labels).
     *
     * Since we cannot connect all frames at the beginning without
     * knowing the total number of frames there will be, we set up the
     * connection for the new frame to perform as needed when clicked.
     */
    void addFrame(QPixmap, int);

    /**
     * Removes the selected frame from the frame preview array (labels).
     */

    void deleteFrame(int);

    /**
     * Gets the position of the frame in labels that the user has selected.
     * Emit the sendFrameSignal with the position of the frame.
     */
    void getFrameClicked(FrameLabel*);

signals:

    /**
     * Signal to tell which frame was clicked.
     */
    void sendFrameClicked(int);

};

#endif // FRAMEPREVIEW_H
