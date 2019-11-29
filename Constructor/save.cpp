#include "save.h"


void Save::saveFile(QString filePath, std::vector<QImage> frames, int dimensions)
{
    QJsonObject json;
    ulong numOfFrames = frames.size();

    json["height"]= dimensions;
    json["width"]=dimensions;
    json["numberOfFrames"]= static_cast<int>(numOfFrames);

    QJsonObject listOfFrames;
    for(ulong i =0; i<numOfFrames; i++) //iterate through all the frames
    {
        QJsonArray individualFrame;
        for(int j=0; j<dimensions; j++) //iterate through a row of pixels
        {
            QJsonArray rowOfPixels;
            for(int k=0; k<dimensions; k++) //iterate through each pixel
            {
                QJsonArray pixel;
                QColor pixelColor =frames[i].pixelColor(j,k);

                //get pixel color from QImage
                int r = pixelColor.red();
                int g = pixelColor.green();
                int b = pixelColor.blue();
                int a = pixelColor.alpha();

                //add rgba to JsonArray
                pixel.append(r);
                pixel.append(g);
                pixel.append(b);
                pixel.append(a);

                rowOfPixels.append(pixel);
            }
            individualFrame.append(rowOfPixels);
        }
        listOfFrames.insert("frame"+QString::number(i), individualFrame);
    }
    json["frames"]= listOfFrames;

    //save JSON file to .ssp
    QJsonDocument document;
    document.setObject(json);
    QFile jsonFile(filePath);
    jsonFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    jsonFile.write(document.toJson());
    jsonFile.close();
}
