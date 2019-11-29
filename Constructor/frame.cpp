#include "frame.h"

Frame::Frame(int width, int height, QObject* parent) : QObject(parent)
{
    image = QImage(width, height, QImage::Format_RGBA8888_Premultiplied);
    image.fill(QColor(255, 255, 255, 0));
}

Frame::Frame(QImage image, QObject* parent):
    QObject(parent),
    image(image)
{
}

Frame::Frame(const Frame& other)
{
    setParent(other.parent());
    image = other.image;
}

Frame&::Frame::operator=(const Frame& other)
{
    setParent(other.parent());
    image = other.image;
    return *this;
}

QImage Frame::GetCopy()
{
    return image.copy();
}

void Frame::scale(int width, int height)
{
    image = image.scaled(width, height, Qt::IgnoreAspectRatio, Qt::FastTransformation);
}

void Frame::reset(QImage image)
{
    image = QImage(image.width(), image.height(), QImage::Format_RGBA8888_Premultiplied);
    image.fill(QColor(255, 255, 255, 0));
}

void Frame::flipH()
{
    image = image.mirrored(true, false);
}

void Frame::flipV()
{
    image = image.mirrored(false, true);
}

void Frame::setColor(int x, int y, QColor color)
{
    image.setPixelColor(x, y, color);
}

QColor Frame::getColor(int x, int y)
{
    return image.pixelColor(x, y);
}

QImage Frame::getImage() {
    return image;
}
