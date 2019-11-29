#include "framepreview.h"
#include "framelabel.h"
#include <QMouseEvent>
#include <QDebug>

FramePreview::FramePreview():
    QWidget(),
    displaySize(100),
    currentLabel(0),
    layout(new QVBoxLayout)
{
    //setting the layout of the frame preview
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(22);
    layout->setSpacing(24);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);

    //adds a default (blank) frame to labels
    QImage blank(1, 1, QImage::Format_RGBA8888_Premultiplied);
    blank.fill(QColor(255, 255, 255, 0));
    FrameLabel* label = new FrameLabel
        (QPixmap::fromImage(blank).scaled(displaySize, displaySize));
    layout->addWidget(label);
    labels.append(label);

    connect(label, &FrameLabel::clicked,
            this, &FramePreview::getFrameClicked);

}

void FramePreview::getFrameClicked(FrameLabel* clicked)
{
    //runs through each frame until it finds the frame that was clicked
    for(int i = 0; i < labels.size(); i++)
    {
        if(labels[i] == clicked)
        {
            emit sendFrameClicked(i);
            break;
        }
    }
}

void FramePreview::receiveFrame(QPixmap img, int index)
{
    labels[index]->setPixmap(img.scaled(displaySize, displaySize));
}

void FramePreview::addFrame(QPixmap img, int index)
{

    FrameLabel* label = new FrameLabel(img.scaled(displaySize, displaySize));
    layout->insertWidget(index, label);
    labels.insert(index, label);

    //makes a new connection for each frame
    connect(label, &FrameLabel::clicked, this, &FramePreview::getFrameClicked);
}

void FramePreview::deleteFrame(int index)
{
    //frame to delete
    FrameLabel* label = labels[index];

    labels.remove(index);
    layout->removeWidget(label);
    delete label;
}


