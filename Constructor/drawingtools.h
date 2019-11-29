#ifndef DRAWINGTOOLS_H
#define DRAWINGTOOLS_H

#include <QWidget>
#include <QPushButton>

/**
 *This class contains all of the drawing tools used in the editor.
 *Drawing tools are: fill, pixel(single pixel draw) and erase.
 */
class DrawingTools: public QWidget
{
    Q_OBJECT
public:
    /**
     * This is the constructor to connect all of our connections and
     * instantiates the instance variables and the button objects.
     */
    DrawingTools();

    /**
     * Indicates to the user which button is currently selected.
     */
    void changeSelectedButton(int);

private:

    QPushButton* fillButton;
    QPushButton* pixelButton;
    QPushButton* eraseButton;

    /**
     * Internal method to set the layout of the 3 drawing buttons within
     * this widget.
     */
    void setButtonLayout();

signals:
    /**
     * Signal to the editor of which drawing tool is currently selected.
     * Fill  -0
     * Pixel -1
     * Erase -2
     */
    void sendType(int);

public slots:
    /**
     * When the fill button is pressed, emits the sendType signal to the editor.
     * Changes the color of the Fill button to denote to the user it is selected.
     */
    void setTypeFill();

    /**
     * When the paintbrush (aka single pixel) button is pressed,
     * emits the sendType signal to the editor.
     * Changes the color of the paintbrush button to denote to the user it is selected.
     */
    void setTypePixel();

    /**
     * When the Erase button is pressed, emits the sendType signal to the editor.
     * Changes the color of the Erase button to denote to the user it is selected.
     */
    void setTypeErase();

};
#endif //DRAWINGTOOLS_H

