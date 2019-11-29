#ifndef FRAME_H
#define FRAME_H
#include <QImage>
#include <QObject>
#include <QColor>

/**
 *  A QImage wrapper that represents a frame in the sprite editor.
 */
class Frame : public QObject

{
    Q_OBJECT

public:
    /**
    * Creates an empty frame with a given width and height.
    */
    Frame(int width, int height, QObject* head = nullptr);

    /**
    * Creates a frame with image.
    */
    Frame(QImage image, QObject* head = nullptr);

    /**
    * Deep copy constructor.
    */
    Frame(const Frame& other);

    /**
    * Assignment operator; rule of three.
    */
    Frame& operator =(const Frame& other);

    /**
    * Scales the image width and height.
    */
    void scale(int width, int height);

    /**
    * Flips the image horizontally.
    */
    void flipH();

    /**
    * Flips the image vertically.
    */
    void flipV();

    /**
    * Resets the image with the image in parameter.
    */
    void reset(QImage image);

    /**
    * Gets the deep copy of the image.
    */
    QImage GetCopy();

    /**
    * Sets the color of a given coordinate.
    */
    void setColor(int x, int y, QColor color);

    /**
    * Gets the color of a given coordinate.
    */
    QColor getColor(int x, int y);

    /**
    * Gets the image of a frame.
    */
    QImage getImage();

private:
    /**
     * the backing Qimage for the frame
     */
    QImage image;
};

#endif
