

#include "drawingtools.h"


DrawingTools::DrawingTools():
    QWidget(),
    fillButton(new QPushButton(this)),
    pixelButton(new QPushButton(this)),
    eraseButton(new QPushButton(this))

{
    setButtonLayout();

    //Makes connections between the Drawing buttons and their respective methods
    QObject::connect(this->fillButton,&QPushButton::clicked,
                        this, &DrawingTools::setTypeFill);
    QObject::connect(this->pixelButton,&QPushButton::clicked,
                        this, &DrawingTools::setTypePixel);
    QObject::connect(this->eraseButton,&QPushButton::clicked,
                        this, &DrawingTools::setTypeErase);

}


void DrawingTools::setButtonLayout(){
    //sets all the buttons in a vertical line
    fillButton -> move(0,0);
    pixelButton -> move(0,50);
    eraseButton -> move(0,100);

    //sets the icon picture onto their respective buttons
    QIcon fillIcon;
    fillIcon.addFile(QString::fromUtf8(":/Icons/FillBucket.jpg"), QSize(), QIcon::Normal, QIcon::Off);
    fillButton->setIcon(fillIcon);
    fillButton->setIconSize(QSize(30, 30));

    QIcon pixelIcon;
    pixelIcon.addFile(QString::fromUtf8(":/Icons/PaintBrush.png"), QSize(), QIcon::Normal, QIcon::Off);
    pixelButton->setIcon(pixelIcon);
    pixelButton->setIconSize(QSize(30, 30));

    QIcon eraseIcon;
    eraseIcon.addFile(QString::fromUtf8(":/Icons/Eraser.png"), QSize(), QIcon::Normal, QIcon::Off);
    eraseButton->setIcon(eraseIcon);
    eraseButton->setIconSize(QSize(30, 30));
}


void DrawingTools::setTypeFill()
{
    emit sendType(0);
    changeSelectedButton(0);
}

void DrawingTools::setTypePixel()
{
    emit sendType(1);
    changeSelectedButton(1);
}

void DrawingTools::setTypeErase()
{
    emit sendType(2);
    changeSelectedButton(2);
}

void DrawingTools::changeSelectedButton(int buttonToHighlight){
    fillButton->setStyleSheet("background-color: white");
    pixelButton->setStyleSheet("background-color: white");
    eraseButton->setStyleSheet("background-color: white");

    if(buttonToHighlight == 0)
    {
        fillButton->setStyleSheet("background-color: grey");

    }
    else if(buttonToHighlight == 1)
    {
        pixelButton->setStyleSheet("background-color: grey");

    }
    else
    {
        eraseButton->setStyleSheet("background-color: grey");
    }


}
