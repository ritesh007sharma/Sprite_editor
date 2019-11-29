#ifndef GIFEXPORT_H
#define GIFEXPORT_H

#include <QObject>
#include <QWidget>
//dbzhang800 code
#include "qgifimage.h"

/**
 * GifExport Class is used for exporting a
 * vector of QImages as a gif. GIF export relies
 * on the libary made by dbzhang800
 *
 * https://github.com/dbzhang800/QtGifImage
 */
class GifExport: public QObject
{
    Q_OBJECT

public slots:

    /**
     * public slot that takes in the vector of QImages and the path for
     * the gif to be saved to
     */
    void exportAsGIF(std::vector<QImage>, int, QString);
};

#endif // GIFEXPORT_H
