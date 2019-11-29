#include "editortools.h"
#include "editortoolsspinbox.h"
#include <QSpinBox>

EditorTools::EditorTools():
    QWidget(),

    //instantiaing the buttons and spinbox on the Colors widget
    hButton(new QPushButton(this)),
    vButton(new QPushButton(this)),
    duplicateButton(new QPushButton(this)),
    scaleBox(new EditorToolsSpinBox(this)),
    addButton(new QPushButton(this)),
    resetButton(new QPushButton(this)),
    removeButton(new QPushButton(this))
{
    setButtonLayout();

    //sets up the connections from the editor buttons with their respective methods

    QObject::connect(this -> hButton, &QPushButton::clicked,
                     this, &EditorTools::on_flippedHButton_clicked);
    QObject::connect(this-> vButton, &QPushButton::clicked,
                     this, &EditorTools::on_flippedVButton_clicked);
    QObject::connect(this->duplicateButton, &QPushButton::clicked,
                     this, &EditorTools::on_duplicateButton_clicked);
    QObject::connect(this->scaleBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                     this, &EditorTools::on_scale_changed);
    QObject::connect(this->addButton, &QPushButton::clicked,
                     this, &EditorTools::on_addButton_clicked);
    QObject::connect(this->resetButton, &QPushButton::clicked,
                     this, &EditorTools::on_resetButton_clicked);
    QObject::connect(this->removeButton, &QPushButton::clicked,
                     this, &EditorTools::on_removeButton_clicked);
}

void EditorTools::setButtonLayout(){

    //sets up the positions of the buttons and spinbox on the widget
    hButton ->           move(0, 0);
    vButton ->           move (120, 0);
    duplicateButton ->   move (100, 50);
    addButton->          move(0, 50);
    resetButton->        move(0, 100);
    removeButton->       move(110, 100);
    scaleBox->           move(90, 150);

    QLabel *scale = new QLabel(this);
    scale->setText("Scale Factor");
    scale->move(0,155);

    //sets the text on each button
    hButton->setText("Flip Horizontal");
    vButton->setText("Flip Vertical");
    addButton->setText("Add Frame");
    duplicateButton->setText("Duplicate Frame");
    resetButton->setText("Reset Frame");
    removeButton->setText("Remove Frame");
}

void EditorTools::on_flippedHButton_clicked()
{
    emit flipH();
}

void EditorTools::on_flippedVButton_clicked()
{
    emit flipV();
}

void EditorTools::on_duplicateButton_clicked()
{
    emit duplicate();
}

void EditorTools::on_scale_changed(int val)
{
    emit scale(val);
}

void EditorTools::on_addButton_clicked()
{
    emit addFrame();
}

void EditorTools::on_removeButton_clicked()
{
    emit removeFrame();
}

void EditorTools::on_resetButton_clicked()
{
    emit resetFrame();
}

