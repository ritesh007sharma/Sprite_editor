#include "framelabel.h"


FrameLabel::FrameLabel(QPixmap img):
    QLabel(),
    displayDim(100)
{
    //setting the dimensions of each of the frames in the frame preview
    setFixedSize(displayDim, displayDim);
    setStyleSheet("QLabel { background-image: url(:/background/background.png);}");
    //displays the small frame image onto the frame preview
    setPixmap(img.scaled(displayDim, displayDim));
}

void FrameLabel::mouseReleaseEvent(QMouseEvent*)
{
    //simply here to alert the framePreview that this frame was pressed
    emit clicked(this);
}
