#ifndef LOAD_H
#define LOAD_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
/**
 * The Load class is used for loading json file
 * into the sprite editor.
 */
class Load : public QObject
{
    Q_OBJECT

public slots:

    /**
     * Open takes in a filename and will open the corresponding
     * file coverting the JSON .ssp file into a vector of QImages
     * and emit the sendVectorOfFrames signals
     */
    void open(QString filename);

signals:
    /**
     * Signal is used to send the vector of QImages
     */
    void sendVectorOfFrames(std::vector<QImage>);

};

#endif // LOAD_H
