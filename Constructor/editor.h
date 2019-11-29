#ifndef EDITOR_H
#define EDITOR_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QWidget>
#include <QPainter>

/**
 * Creates a graphicsScene object that displays a sprite frame and a rectangle
 * over where the current pixel will be drawn
 */
class Editor : public QGraphicsScene
{
    Q_OBJECT

private:
    /**
     * Holds the dimensions of the current frame (in pixels per side)
     */
    int displayDim;

    /**
     * Holds the width and height of the editor panel in pixels
     */
    int gridDim;

    /**
     * Holds the number of pixels per displayed pixel
     * (the width and height of each displayed pixel in pixels)
     */
    int pixelWidth;

    /**
     * The rectangle that hovers over where the next pixel will be drawn
     */
    QGraphicsRectItem* rect;

    /**
     * The object to which the sprite frame is displayed to appear in the editor panel
     */
    QGraphicsPixmapItem* img;

    /**
     * The color of the cursor that highlights what pixel will be selected
     */
    QColor highlightColor;

    /**
     * The color that is currently being used to draw
     */
    QColor currentColor;

    /**
     * Represents what drawing tool is set (fill, draw, erase)
     */
    int toolType;

    /**
     * Is true while the mouse is being held
     */
    bool isPressed;

    /**
     * The current frame column that the mouse position corresponds to
     */
    int currX;

    /**
     * The current frame row that the mouse position corresponds to
     */
    int currY;

    /**
     * Returns the pixel position of a number that is associated with its grid position.
     * Truncates pixel value to be evenly divisible by pixelWidth
     */
    int getGridPos(int);

    /**
     * Sends a drawing signal to the model based on the currentTool
     */
    void sendSignal(int, int);

public:
    /**
     * Initializes the Editor, setting the dimensions and default tools/colors
     */
    Editor(QObject* parent);

public slots:
    /**
     * Moves the highlight rectangle and continues drawing if the mouse is held
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

    /**
     * Resets isPressed and sets the highlight rectangle back to the original color
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    /**
     * Sets isPressed and sends a draw signal to the model. Also changes highlight
     * rectangle color to current color;
     */
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    /**
     * Sets the currently displayed image to be the new QImage
     */
    void changeFrame(QPixmap, int);

    /**
     * changes the gridDim (the pixel x pixel dimensions of the image)
     */
    void setDim(int);

    /**
     * Changes the tool (fill, draw, erase)
     */
    void changeTool(int);

    /**
     * changes the current color
     */
    void changeColor(QColor);

signals:
    /**
     * signals to the model to paint a pixel a given color
     */
    void setPixel(int, int, QColor);

    /**
     * signals to the model to fill from a pixel with a given color
     */
    void fillPixel(int, int, QColor);

    /**
     * signals to the model to erase a pixel
     */
    void erasePixel(int, int, QColor);

    /**
     * A signal to tell the model to draw a line between the two pixels
     */
    void drawLine(int, int, int, int, QColor);
};

#endif // EDITOR_H
