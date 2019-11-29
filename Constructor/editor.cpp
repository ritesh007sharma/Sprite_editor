#include "editor.h"
#include <QUrl>
#include <QtGui>
#include <QGraphicsPixmapItem>
#include <cmath>

Editor::Editor(QObject* parent):
    QGraphicsScene(parent),
    displayDim(768),
    gridDim(8),
    pixelWidth(displayDim/gridDim),
    rect(new QGraphicsRectItem(0, 0, pixelWidth, pixelWidth)),
    highlightColor(255, 255, 255, 160),
    currentColor(0, 0, 0),
    toolType(1),
    isPressed(false),
    currX(-1),
    currY(-1)
{
    //load and set the background image
    QPixmap background(":/background/background.png");
    background= background.scaled(displayDim, displayDim);
    rect->setBrush(highlightColor);
    rect->setPen(Qt::NoPen);
    this->addPixmap(background);

    //set a blank Pixmap and same the QGraphicsScene to set later
    QImage blank(gridDim, gridDim, QImage::Format_RGBA8888_Premultiplied);
    blank.fill(QColor(255, 255, 255, 0));
    QPixmap blankMap= QPixmap::fromImage(blank).scaled(displayDim, displayDim);
    img = addPixmap(blankMap);
    addItem(rect);
}

void Editor::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF pos = event->scenePos();
    //get the grid position of the mouse
    int x = static_cast<int>(pos.x() / pixelWidth);
    int y = static_cast<int>(pos.y() / pixelWidth);

    //only send a signal to the model if the mouse is in a new square
    bool sameSquare = x == currX && y == currY;
    if(!sameSquare){
        if (isPressed)
        {
            //draw a line if we have done more than just traverse one pixel
            if(toolType == 1 && (std::abs(currX-x) > 1 || std::abs(currY-y) > 1))
            {
                emit drawLine(currX, currY, x, y, currentColor);
            }
            currX = x;
            currY = y;
            sendSignal(currX, currY);
        }
        //change the highlighted pixel
        rect->setRect(getGridPos(static_cast<int>(pos.x())), getGridPos(static_cast<int>(pos.y())),
                      pixelWidth, pixelWidth);
    }
}

void Editor::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    isPressed = true;
    QPointF pos = event->scenePos();
    currX = static_cast<int>(pos.x() / pixelWidth);
    currY = static_cast<int>(pos.y() / pixelWidth);
    //if we are erasing, dont change the highlight color
    if(toolType != 2)
    {
        rect->setBrush(currentColor);
    }
    //tell the model to draw/erase
    sendSignal(currX, currY);
}

void Editor::mouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
    rect->setBrush(highlightColor);
    isPressed = false;
    currX = -1;
    currY = -1;
}

void Editor::sendSignal(int x, int y)
{
    if(toolType == 0)
    {
        emit fillPixel(x, y, currentColor);
    }
    else if (toolType == 1)
    {
        emit setPixel(x, y, currentColor);
    }
    else
    {
        emit erasePixel(x, y, currentColor);
    }
}

void Editor::setDim(int dim)
{
    gridDim = dim;
    pixelWidth = displayDim / gridDim;
}

int Editor::getGridPos(int pos)
{
    pos = pos / pixelWidth;

    //don't allow a grid position >= gridDim
    if(pos >= gridDim)
    {
        pos = gridDim-1;
    }
    return pos * pixelWidth;;
}

void Editor::changeFrame(QPixmap newFrame, int)
{
    img->setPixmap(newFrame.scaled(displayDim, displayDim));
}

void Editor::changeTool(int tool)
{
    toolType = tool;
}

void Editor::changeColor(QColor newColor)
{
    currentColor = newColor;
}
