#ifndef SAVE_H
#define SAVE_H

#include <QObject>
#include <QWidget>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <QDebug>

/**
 * The save class is used to save a vector of QImages
 * to a JSON file.
 */
class Save : public QObject
{
    Q_OBJECT

public slots:

    /**
     * Converts the vector of QImages to a JSON object and saves it to the
     * specifed file name.
     */
    void saveFile(QString filename, std::vector<QImage> frames, int dimensions);
};

#endif // SAVE_H
