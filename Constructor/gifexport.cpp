#include "gifexport.h"

void GifExport::exportAsGIF(std::vector<QImage> frames, int dim, QString filePath)
{
    QGifImage gif(QSize(dim,dim));
    gif.setDefaultDelay(100);

    for(ulong i=0; i<frames.size(); i++)
    {
        gif.addFrame(frames[i]);
    }
    gif.save(filePath);
}
