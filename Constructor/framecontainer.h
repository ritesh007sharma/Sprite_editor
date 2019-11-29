#ifndef FRAMECONTAINER_H
#define FRAMECONTAINER_H

#include <QPoint>
#include <QColor>
#include <QImage>
#include <QPixmap>
#include <unordered_map>
#include <sstream>
#include <frame.h>

/**
 * The FrameContainer class is the backend data structure
 * for the sprite editior and contains the vector of frames
 * data structure
 */
class FrameContainer : public QObject
{
    Q_OBJECT

public slots:

    /**
    * Erases the coordinate in the current frame.
    */
    void erase(int x, int y);

    /**
    * Request the frame at a given index.
    */
    void requestFrame(int);

    /**
    * Duplicates the current frame.
    */
    void duplicateFrame();

    /**
    * Sets the given index to the current frame.
    */
    void setCurrentFrame(int);

    /**
    * Deletes the current frame.  If there is only one frame, clears it.
    */
    void deleteCurrentFrame();

    /**
    * Flips the frame horizontally.
    */
    void flipFrameH();

    /**
    * Flips th e frame vertically.
    */
    void flipFrameV();

    /**
    * Requests the dimension of frames.
    */
    void requestDimension();

    /**
    * Bucket fill.  Colors all adjacent pixels of the same color with a depth
    * first search.
    */
    void fillPixel(int x, int y, QColor c);

    /**
    * Sets the color of a given pixel in the current frame.
    */
    void setPixel(int x, int y, QColor color);

    /**
    * Request the number of frames.
    */
    void requestFrameCount();

    /**
    * Clears the current frame.
    */
    void clearFrame();

    /**
    * Creates a frame from the QImage and adds it to the vector of frames.
    */
    void loadFrame(QImage);

    /**
    * Creates a new frame.
    */
    void newFrame();

    /**
    * Scale the frames up and down based on the scale factor.
    */
    void scaleFrames(int);

    /**
    * Clears all frames in the current session and loads a previous session.
    */
    void loadFile(std::vector<QImage>);

    /**
    * Requests a frame, emitting a signal specifically for displaying animated
    * frames.
    */
    void requestAnimatedFrame(int);

    /**
     * draws a line of pixels between the two pixel locations
     */
    void drawLine(int, int, int, int, QColor);

public:

    /**
    * Creates a frame container, setting the dimension to 8 x 8 and creating a
    * blank single frame.
    */
    FrameContainer(QObject *parent = nullptr);

    /**
    * Deconstructor.
    */
    virtual ~FrameContainer();

    /**
    * Gets the QImages of all frames.
    */
    std::vector<QImage> getFrames();

    /**
    * Gets the dimension.
    */
    int getDimension();

private:

    /**
    * All frames in the current session.
    */
    std::vector<Frame> frames;

    /**
    * The dimension of all frames.
    */
    int frameDim;

    /**
    * The index of the current frame.
    */
    int currentFrame;

    /**
    * Checks if a coordinate is valid.
    */
    bool isValidCoordinate(int x, int y);

    /**
    * Checks if an index is valid.
    */
    bool isValidIndex(int index);

    /**
    * Sets the color of a pixel.
    */
    void setPixelHelper(int x, int y, QColor color);

    /**
    * Recursive method of fillPixel.
    */
    void recursiveFill(int x, int y, QColor originalColor, QColor newColor);



signals:

    /**
    * Sends frame dimension.
    */
    void returnDimensions(int);

    /**
    * Sends the number of frames.
    */
    void sendFrameCount(int);

    /**
    * Sends the frame's image and index.
    */
    void sendFrame(QPixmap, int);

    /**
    * Sends the index of an added frame and its image.
    */
    void addFrame(QPixmap, int);

    /**
    * Sends the index of a removed frame.
    */
    void removeFrame(int);

    /**
    * Sends a frame's image.  For animated frame only.
    */
    void sendAnimatedFrame(QPixmap);
};

#endif
