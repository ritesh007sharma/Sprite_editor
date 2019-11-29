#include <framecontainer.h>
#include <iostream>
#include <QDebug>

using namespace std;

FrameContainer::FrameContainer(QObject *parent)
    : QObject(parent)
{
    currentFrame = -1;
    frameDim = 8;
    frames.clear();
    newFrame();
}

FrameContainer::~FrameContainer(){}

void FrameContainer::duplicateFrame()
{
    Frame duplicate = frames[static_cast<ulong>(currentFrame)];
    auto duplicateFrame = frames.begin() + currentFrame;
    frames.insert(duplicateFrame, duplicate);
    currentFrame++;
    addFrame(QPixmap::fromImage(frames[static_cast<ulong>(currentFrame)].getImage()), currentFrame);
}

void FrameContainer::setCurrentFrame(int index)
{
     if(isValidIndex(index))
     {
        currentFrame = index;
        requestFrame(currentFrame);
     }
}

void FrameContainer::deleteCurrentFrame()
{
    if (frames.size() > 1) {
        frames.erase(frames.begin() + currentFrame);
        if(currentFrame != 0)
        {
            currentFrame--;
        }
        emit removeFrame(currentFrame);
        emit requestFrame(currentFrame);
    } else {
        clearFrame();
    }
}

void FrameContainer::requestFrame(int index)
{
    if (isValidIndex(index))
        emit sendFrame(QPixmap::fromImage(frames[static_cast<ulong>(index)].getImage()), index);
}

void FrameContainer::flipFrameH()
{
    frames[static_cast<ulong>(currentFrame)].flipH();
    emit sendFrame(QPixmap::fromImage(frames[static_cast<ulong>(currentFrame)].getImage()), currentFrame);
}

void FrameContainer::flipFrameV()
{
    frames[static_cast<ulong>(currentFrame)].flipV();
    emit sendFrame(QPixmap::fromImage(frames[static_cast<ulong>(currentFrame)].getImage()), currentFrame);
}

void FrameContainer::requestDimension()
{
    emit returnDimensions(frameDim);
}

void FrameContainer::fillPixel(int x, int y, QColor newColor) // We can use QPoint instead of x, y
{
    if (isValidCoordinate(x, y))
    {
        QColor originalColor = frames[static_cast<ulong>(currentFrame)].getColor(x, y);
        recursiveFill(x, y, originalColor, newColor);
        requestFrame(currentFrame);
    }
}

void FrameContainer::erase(int x, int y)
{
    setPixel(x, y, QColor(0,0,0,0));
    requestFrame(currentFrame);
}

void FrameContainer::recursiveFill(int x, int y, QColor originalColor, QColor newColor)
{
    if (isValidCoordinate(x, y)) {
        QColor currentColor = frames[static_cast<ulong>(currentFrame)].getColor(x, y);

        if (newColor != currentColor && originalColor == currentColor)
        {
            setPixelHelper(x, y, newColor);

            // Call on adjacent neighbors.
            recursiveFill(x-1, y, originalColor, newColor);
            recursiveFill(x+1, y, originalColor, newColor);
            recursiveFill(x, y-1, originalColor, newColor);
            recursiveFill(x, y+1, originalColor, newColor);
        }
    }
}

void FrameContainer::setPixel(int x, int y, QColor color) // We can use QPoint instead of x, y
{
    setPixelHelper(x, y, color);
    requestFrame(currentFrame);
}

void FrameContainer::setPixelHelper(int x, int y, QColor color)
{
    if (isValidCoordinate(x, y))
        frames[static_cast<ulong>(currentFrame)].setColor(x, y, color);
}

void FrameContainer::requestFrameCount()
{
    emit sendFrameCount(static_cast<int>(frames.size()));
}

void FrameContainer::clearFrame()
{
    Frame newFrame(frameDim, frameDim);
    frames[static_cast<ulong>(currentFrame)] = newFrame;
    requestFrame(currentFrame);
}

void FrameContainer::loadFile(std::vector<QImage> images)
{
    // Replace current frames with images.
    for (unsigned i = 0; i < images.size(); i++)
    {
        if(i < frames.size())
        {
            frames[i] = Frame(images[i]);
            sendFrame(QPixmap::fromImage(images[i]), static_cast<int>(i));
        }
        else
        {
            frames.push_back(Frame(images[i]));
            addFrame(QPixmap::fromImage(images[i]), static_cast<int>(i));
        }
    }

    // If there are more current frames than images, removes extra frames.
    for (ulong i = frames.size() -1; i >= images.size(); i--)
    {
        frames.pop_back();
        emit removeFrame(static_cast<int>(i));
    }

    currentFrame = 0;
    emit sendFrame(QPixmap::fromImage(frames[0].getImage()), 0);

    frameDim = images[0].width();
    emit returnDimensions(frameDim);
}

void FrameContainer::newFrame()
{
    Frame duplicate(frameDim, frameDim);
    ++currentFrame;
    auto duplicateFrame = frames.begin() + currentFrame;
    frames.insert(duplicateFrame, duplicate);
    emit addFrame(QPixmap::fromImage(frames[static_cast<ulong>(currentFrame)].getImage()), currentFrame);
}

void FrameContainer::scaleFrames(int scale)
{
    for(unsigned i = 0; i < frames.size(); i++) {
        frames[i].scale(scale, scale);
    }
    emit returnDimensions(scale);
    if (scale < frameDim)
    {
        for (ulong i = 0; i < frames.size(); i++)
        {
            ulong frameNum = (i + 1 + static_cast<ulong>(currentFrame)) % frames.size();
            emit sendFrame(QPixmap::fromImage(frames[frameNum].getImage()), static_cast<int>(frameNum));
        }
    }
    frameDim = scale;
}

void FrameContainer::loadFrame(QImage image)
{
    frames.push_back(Frame(image));
}

vector<QImage> FrameContainer::getFrames()
{
    // Add frame images to a vector and return it.
    vector<QImage> ret;
    for (Frame f : frames) {
        ret.push_back(f.getImage());
    }

    return ret;
}

int FrameContainer::getDimension()
{
    return frameDim;
}

bool FrameContainer::isValidCoordinate(int x, int y)
{
    return 0 <= x && x < frameDim && 0 <= y && y < frameDim;
}

bool FrameContainer::isValidIndex(int index)
{
    int numFrames = static_cast<int>(frames.size());
    return 0 <= index && index < numFrames;
}

void FrameContainer::requestAnimatedFrame(int index)
{
    if(isValidIndex(index))
        emit sendAnimatedFrame(QPixmap::fromImage(frames[static_cast<ulong>(index)].getImage()));
}

//This implementation of the DDA algorithm was written with
//help from Geeks for Geeks: Digital Differential Analyzer
void FrameContainer::drawLine(int x1, int y1, int x2, int y2, QColor color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int count = abs(dx);
    if(count < abs(dy))
    {
        count = abs(dy);
    }
    float xStep = dx / static_cast<float>(count);
    float yStep = dy / static_cast<float>(count);
    float x = x1;
    float y = y1;
    for (int i = 0; i <= count; i++)
    {
        frames[static_cast<ulong>(currentFrame)].setColor(static_cast<int>(x), static_cast<int>(y), color);
        x += xStep;
        y += yStep;
    }
}
