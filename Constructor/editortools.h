#ifndef EDITORTOOLS_H
#define EDITORTOOLS_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include "editortoolsspinbox.h"

/**
 * This class contains all of the editing tools used in the editor.
 *
 * Editing tools are:
 * Horizontal frame flip,
 * vertical frame flip,
 * duplicate frame
 * scale pixel,
 * add frame,
 * reset frame,
 * remove frame.
 */
class EditorTools : public QWidget
{
    Q_OBJECT

public:
    /**
     * Creates an Editor Tools widget which holds buttons for performing
     * various operations to the current image
     */
    EditorTools();

private:
    /**
     * button for flipping the frame horizontally
     */
    QPushButton* hButton;

    /**
     * button for flipping the frame vertically
     */
    QPushButton* vButton;

    /**
     * button for duplicating the frame
     */
    QPushButton* duplicateButton;

    /**
     * button for scaling the frames
     */
    QSpinBox* scaleBox;

    /**
     * button for adding a frame
     */
    QPushButton* addButton;

    /**
     * button for clearing the frame
     */
    QPushButton* resetButton;

    /**
     * button for removing the frame
     */
    QPushButton* removeButton;

    /**
     * Sets the layout of the buttons within the widget.
     * Sets labels on the buttons as well.
     */
    void setButtonLayout();

private slots:
    /**
     * When the horizontal flipped button is pressed, emits the flipH signal
     * to the editor.
     */
    void on_flippedHButton_clicked();

    /**
     * When the vertical flipped button is pressed, emits the flipV signal
     * to the editor.
     */
    void on_flippedVButton_clicked();

    /**
     * When the duplicate frame button is pressed, emits the duplicate signal
     * to the editor.
     */
    void on_duplicateButton_clicked();

    /**
     * When the scaling on the spibox is changed, emits the flipH signal
     * to the editor.
     */
    void on_scale_changed(int);

    /**
     * When the add frame button is pressed, emits the scale(int) signal
     * to the editor.
     */
    void on_addButton_clicked();

    /**
     * When the reset frame button is pressed, emits the resetFrame signal
     * to the editor.
     */
    void on_resetButton_clicked();

    /**
     * When the remove frame button is pressed, emits the removeFrame signal
     * to the editor.
     */
    void on_removeButton_clicked();

/**
 * Signals that send to the editor which button/action was chosen.
 */
signals:
    /**
     * signals to the model to flip the current frame horizontally
     */
    void flipH();

    /**
     * signals to the model to flip the current frame vertically
     */
    void flipV();

    /**
     * signals to the model to make a copy of the current frame
     */
    void duplicate();

    /**
     * signals to the model to scale the frames to size x size
     */
    void scale(int size);

    /**
     * signals to the model to add a blank frame
     */
    void addFrame();

    /**
     * signals to the model to clear the current frame
     */
    void resetFrame();

    /**
     * signals to the model to remove the current frame
     */
    void removeFrame();

};
#endif // EDITORTOOLS_H
