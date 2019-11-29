#include "load.h"

void Load::open(QString filePath)
{
    //load the saved file into a string
    QString val;
    QFile file;
    file.setFileName(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    //convert string to JSON
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sprite = d.object();

    QJsonObject frameArray = sprite.value(QString("frames")).toObject();
    int height = sprite.value(QString("height")).toInt();
    int width = sprite.value(QString("width")).toInt();
    int numOfFrames = sprite.value(QString("numberOfFrames")).toInt();

    std::vector<QImage> vectOfFrames;

    // "i" iterates through each frame
    for(int i=0; i<numOfFrames; i++)
    {
        QImage image(height, width, QImage::Format_ARGB32);
        QJsonArray frame = frameArray["frame"+QString::number(i)].toArray();

        //"j" iterates through each row of pixels
        for(int j=0; j<width; j++)
        {
            QJsonArray pix = frame[j].toArray();

            //iterates through each pixel in a row of pixels
            for(int k=0; k<height; k++)
            {
                QJsonArray pixel = pix[k].toArray();
                QColor rgbaPixel;

                rgbaPixel.setRgb(pixel[0].toInt(),pixel[1].toInt(),pixel[2].toInt(),pixel[3].toInt());
                image.setPixelColor(j,k,rgbaPixel);
            }
        }
        vectOfFrames.push_back(image);
    }
    emit sendVectorOfFrames(vectOfFrames);
}
