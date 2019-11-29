#include "animatedpreview.h"
#include <QDebug>

AnimatedPreview::AnimatedPreview():
    QWidget(),
    display(new QLabel(this)),
    slider(new QSlider(this)),
    maxLabel(new QLabel(this)),
    minLabel(new QLabel(this)),
    displayTime(200),
    frameCount(1),
    displayedFrame(0),
    scaledSize(100)
{
    QPixmap* p = new QPixmap(8, 8);
    p->fill(QColor(255, 255, 255, 0));
    display->setPixmap(p->scaled(100, 100));
    display->move(10, 40);

    minLabel->setText("0");
    minLabel->move(15, 140);
    maxLabel->setText("30");
    maxLabel->move(85, 140);

    slider->setValue(1000/displayTime);
    slider->setMaximum(30);
    slider->setMinimum(0);
    slider->setTickInterval(5);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setOrientation(Qt::Horizontal);
    slider->move(15, 160);

    refreshTimer.start(displayTime);

    connect(this->slider,
            &QSlider::valueChanged,
            this,
            &AnimatedPreview::changeDisplayTime);
    connect(&this->refreshTimer,
            &QTimer::timeout,
            this,
            &AnimatedPreview::changeDisplay);
}

void AnimatedPreview::changeDisplayTime(int fps)
{
    refreshTimer.stop();
    if (fps != 0)
    {
        displayTime = 1000 / fps;
        refreshTimer.start(displayTime);
    }
}

void AnimatedPreview::changeDisplay()
{
    emit requestFrame(displayedFrame % frameCount);
}

void AnimatedPreview::receiveDisplay(QPixmap img)
{
    display->setPixmap(img.scaled(scaledSize, scaledSize));
    displayedFrame++;
}

//the QImage and Int are not used by this slot,
//but generic singals send this
void AnimatedPreview::addFrame(QPixmap, int)
{
    frameCount++;
    displayedFrame = 0;
}

//The int isnt used by this slot,
//but connects to generic signals that send
void AnimatedPreview::removeFrame(int)
{
    frameCount--;
    displayedFrame = 0;
}
